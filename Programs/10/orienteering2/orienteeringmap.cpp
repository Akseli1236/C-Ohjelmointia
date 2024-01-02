/*
* COMP.CS.110 Ohjelmointi 2: Rakenteet / Programming 2: Structures
* Project3: Suunnistus / Orienteering
* Ohjelman kirjoittaja ( Täytä omilla tiedoillasi )
* Nimi: Akseli Ahonen
* Opiskelijanumero: 150313812
* Käyttäjätunnus: tbakah ( Git-repositorion hakemistonimi. )
* E-Mail: akseli.ahonen@tuni.fi
*
* Huomioita ohjelmasta ja sen toteutuksesta:
*
*
* */


#include "orienteeringmap.hh"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <set>


using std::cout, std::endl, std::string;


OrienteeringMap::OrienteeringMap(): map_(), points_(), routes_()
  //Luodaan Kartta-olio
{}

OrienteeringMap::~OrienteeringMap()
{
    //Destrucotri poistaa kaikki pointterit
    //ja vapauttaa niiden varaaman muistin
    //Kun oliota ei enää tarvita
    for (auto& [route,point_object]: routes_){
        while (point_object != nullptr) {
            Routes* release = point_object;
            point_object = point_object->next;

            delete release;
        }
    }
}

void OrienteeringMap::set_map_size(int width, int height)
{
    //Asettaa kartalle koon parametrien width ja height avulla
    //Lopputuloksena on tyhjä suunnistuskartta.

    //Käydään läpi korkeus ja jokaiselle riville
    //tulostetaan pisteitä leveyden verran
    //ennen kuin siirytään uudelle riville.
    for (int y = 0; y < height; y++){
        std::vector< std::shared_ptr<string> > line;
        for (int x = 0; x < width; x++){
            std::shared_ptr< string > nextSpot = std::make_shared<string>(".");
            line.push_back(nextSpot);
        }
        map_.push_back(line);
    }
}

void OrienteeringMap::add_point(std::string name, int x, int y, int height
                                , char marker)
{
    //Luo olion rastista ja sen jälkeen lisää sen kartalle
    //Annettujen koordinaattien perusteella.
    //Saa parametrina rastin nime, sijainnin x:n ja y:n suhteen
    //sekä korkeuden että karttamerkin

    unsigned long xCoord = x;
    unsigned long yCoord = y;

    //Tarkastetaan onko koordinaatit mahdollisia ja
    //Kartan sisällä.
    if (x > 0 && y > 0){
        if (yCoord <= map_.size() && xCoord <= map_.at(0).size()){
            points_[name] = Route(name,x,y,height,marker);
            *map_.at(y-1).at(x-1) = points_[name].getMarker();
        }
    }
}

bool OrienteeringMap::connect_route(std::string from, std::string to
                                    , std::string route_name)
{
    //Lisää rastit osaksi reittiä jos kumpikin rasteista on olemassa
    //Saa parametreina alkurastin ja loppurastin sekä reitin nimen
    //jonne rasti lisätään.
    //Palauttaa arvon false jos toinen tai molemmat rastit puuttuvat kartalta
    //true jos molemmat rastit löytyvät

    if (points_.find(from) == points_.end() || points_.find(to) == points_.end()){
        return false;
    }

    //Jos reitillä ei ole vielä yhtään rastia sinne lisätään
    //Alku- ja loppurasti.
    //Muulloin vain loppurasti, koska alkurasti on jo tallennettu.
    Routes* route = routes_[route_name];
    if (route == nullptr){
        routes_[route_name] = new Routes{points_[from], nullptr};
        routes_[route_name]->next = new Routes{points_[to], nullptr};

    }else{
        while (route->next != nullptr) {
            route = route->next;
        }
        route->next = new Routes{points_[to], nullptr};
    }
    return true;
}

void OrienteeringMap::print_map() const
{

    //Tulostaa kartan rasteineen.

    int height = map_.size();
    int width = map_.at(0).size();
    cout << " ";

    //Tulostetaan aluksi ensimmäisen rivin sisältävät numerot
    for (int xCoord = 0; xCoord < width; xCoord++){
        if (xCoord < 9){
            cout  << "  " << xCoord + 1;
        }else{
            cout  << " " << xCoord + 1;
        }
    }
    cout << endl;

    //Tulostetaan pystyrivin numerot ja rastit
    for (int yCoord = 0; yCoord < height; yCoord++){
        if (map_.size() > 9 && yCoord+1 < 10){
            cout << " " << yCoord + 1 << "  ";
        }else{
            cout << yCoord + 1 << "  ";
        }

        for (int xCoord = 0; xCoord < width; xCoord++){
            cout <<  *map_.at(yCoord).at(xCoord) << "  ";
        }
        cout << endl;
    }
}

void OrienteeringMap::print_routes() const
{
    //Tulostaa kaikki reitit aakkosjärjestyksessä.
    cout << "Routes:" << endl;
    for (const auto& [route_name,point_object]: routes_){
        cout << " - " << route_name << endl;
    }

}

void OrienteeringMap::print_points() const
{
    //Tulostaa kaikki rastit ja niiden karttamerkit
    //aakkosjärjestyksessä.
    cout << "Points:" << endl;
    for (const auto& [route_name, point_object]: points_){
        cout << " - " << route_name << " : " << point_object.getMarker() << endl;
    }
}

void OrienteeringMap::print_route(const std::string &name) const
{
    //Tulostaa kaikki reittien nimet.
    //Saa parametreina reitin nimen

    //Tarkastetaan onko reittiä olemassa
    if (routes_.find(name) == routes_.end()){
        cout << "Error: Route named " << name << " can't be found" << endl;
    }else{
        for (const auto& [route_name, point_object]: routes_)
            if (route_name == name){
                cout << point_object->point.getName() << endl;
                Routes* print = point_object->next;
                while (print != nullptr) {
                    cout << " -> " << print->point.getName() << endl;
                    print = print->next;
                }
            }
    }

}

void OrienteeringMap::route_length(const std::string &name) const
{
    //Tulostaa parametrina saadun reitin pituuden.

    //Tarkastetaan onko reittiä olemassa
    if (routes_.find(name) == routes_.end()){
        cout << "Error: Route named " << name << " can't be found" << endl;
    }else{
        Routes* point = routes_.at(name);
        float lenght = 0;
        int x_pow = 0;
        int y_pow = 0;

        //Käydään läpi kaikki reitti-oliot ja lasketaan niiden etäisyys seuraavaan
        while (point->next != nullptr) {

            x_pow = pow(points_.at(point->point.getName()).getx()
                        -points_.at(point->next->point.getName()).getx(),2);
            y_pow = pow(points_.at(point->point.getName()).gety()
                        -points_.at(point->next->point.getName()).gety(),2);
            lenght += sqrt(x_pow+y_pow);
            point = point->next;
        }
        //Tulostetaan kahden numeron tarkkuudella reitin pituus.
        cout << std::setprecision(2) << "Route " << name << " length was "
         << lenght << endl;
    }
}

void OrienteeringMap::greatest_rise(const std::string &point_name) const
{

    //Etsii korkeimman nousun, joka kuljetaan tietyltä pisteeltä
    //eteenpäin.
    //Parametrina on haluttu aloitusrasti.

    int max_height = 0;
    int current_height = 0;
    int original_height = 0;
    int rise = 0;
    std::map<string, int> inclouded_routes {};
    bool found = false;

    //Käydään läpi kaikki reitit.
    for (const auto& [names, point_object] : routes_){
        current_height = 0;
        found = false;
        Routes* point = point_object;
        //Etsitään se kohta, jossa on haluttu aloituspiste
        while (point->next != nullptr) {
            if (point->point.getName() == point_name){
                break;
            }else{
                point = point->next;
            }
        }
        //Käydään aloituspisteestä alkaen läpi jokaisen
        //Rastin korkeus ja seuraava laskeva välimatka
        //päättää testauksen, jos ei saavuteta viimeistä rastia.
        while (point != nullptr) {
            if (point->point.getHeight() < current_height){
                break;
            }else{
                //Kertoo tällä hetkellä läpikäytävän rastin
                //korkeuden
                current_height = point->point.getHeight();

                //Jos Rasti löytyy niin tallennetaan alkuperäinen korkeus
                if (point->point.getName() == point_name){
                    original_height = point->point.getHeight();
                    found = true;
                }

                //Jos rasti löydettiin ja maksimikorkeus on
                //vähemmän kuin nykyinen korkeus
                //maksimikorkeus kasvaa.
                if (found && max_height < current_height){
                    max_height = current_height;
                }
                point = point->next;
            }
        }
        //Jos maksimikorkeus on vähemmän tai yhtäsuuri ja
        //löydettiin rasti niin lisätään reitin nimi
        //ja sen maksimikorkeus.
        if (max_height <= current_height && found){
            inclouded_routes [names] = max_height;
        }
    }
    rise = max_height - original_height;

    //Jos rastia ei löytynt reitiltä
    if (inclouded_routes.size() == 0){
        cout << "Error: Point named " << point_name << " can't be found" << endl;
    //Jos nousua ei tapahtunut
    }else if (rise == 0){
        cout << "No route rises after point " << point_name << endl;
    //Tulostetaan nousu ja reitit
    }else{
        cout << "Greatest rise after point " << point_name << ", " << rise;
        cout << " meters, is on route(s):" << "\n";
        for (auto& [route, heigth] : inclouded_routes){
            if (heigth == max_height){
                 cout << " - " << route << endl;
            }
        }
    }
}


