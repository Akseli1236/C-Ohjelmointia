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




#ifndef ROUTE_HH
#define ROUTE_HH
#include <string>
#include <vector>
#include <memory>

//Luokka Route luo rasti-olion halutuilla parametreilla.

class Route
{
public:
    //Konstruktorit
    Route();
    Route(std::string name, int x, int y, int height, char marker);

    //Palauttaa nimen
    std::string getName() const;

    //Palautta x-koordinaatin
    int getx() const;

    //Palautta y-koordinaatin
    int gety() const;

    //Palautta korkeuden
    int getHeight() const;

    //Palautta karttamerkin
    char getMarker() const;

private:
    std::string name_;
    int x_;
    int y_;
    int height_;
    char marker_;
};

#endif // ROUTE_HH
