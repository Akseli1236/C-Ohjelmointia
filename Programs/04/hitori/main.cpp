/* Hitori
 *
 * Kuvaus:
 *   Ohjelma toteuttaa Hitori-pelin. Pelissä on peliruudukko kooltaan
 * 5 x 5. Kukin ruutu sisältää jonkin numeroista 1-5. Vaaka- ja
 * pystyriveillä voi aluksi olla useita samoja numeroita, mutta
 * tarkoituksena on poistaa numeroita niin, että kullakin vaaka- ja
 * pystyrivillä on kutakin numeroa vain yksi tai ei yhtään. Kuitenkaan
 * vierekkäisten ruutujen numeroita ei saa poistaa, eikä mikään jäljelle
 * jäävä numero (ruutu) saa jäädä irralleen muista, eli sen ympäriltä
 * (yläpuolelta, alapuolelta, vasemmalta, oikealta) ei saa poistaa
 * kaikkia numeroita.
 *   Aluksi käyttäjältä kysytään, täytetäänkö peliruudukko satunnaisesti
 * arvottavilla luvuilla 1-5 vai käyttäjän valitsemilla 25 luvulla.
 * Ensimmäisessä vaihtoehdossa käyttäjältä kysytään satunnaisluku-
 * generaattorin siemenlukua ja jälkimmäisessä häntä pyydetään syöttämään
 * 25 lukua.
 *   Joka kierroksella käyttäjältä kysytään poistettavan numeron
 * koordinaatteja eli kahta lukua. Peli päättyy pelaajan voittoon,
 * jos peliruudukon kaikilla vaaka- ja pystyriveillä esiintyy kukin
 * numero 1-5 korkeintaan kerran. Peli päättyy pelaajan häviöön,
 * jos hän poistaa jo poistetun numeron viereisen numeron tai jos
 * jokin numero jää irralleen muista.
 *   Ohjelma tarkistaa annetut koordinaatit. Koordinaattien pitää olla
 * peliruudukon sisällä, ja niiden osoittaman ruudun pitää sisältää
 * numero, eli jo poistettua numeroa ei voi poistaa toiseen kertaan.
 *   Pelin päättyessä kerrotaan, voittiko vai hävisikö pelaaja.
 *
 * Ohjelman kirjoittaja ( Täytä omilla tiedoillasi )
 * Nimi: Akseli Ahonen
 * Opiskelijanumero: 150313812
 * Käyttäjätunnus: tbakah ( Git-repositorion hakemistonimi. )
 * E-Mail: akseli.ahonen@tuni.fi
 *
 * Huomioita ohjelmasta ja sen toteutuksesta:
 * En osannut toteuttaa häviön testaamista mitenkään järkevästi.
 *
 * */

#include <iostream>
#include <vector>
#include <random>


using namespace std;

const unsigned int BOARD_SIDE = 5;
const unsigned char EMPTY = ' ';

// Muuttaa annetun numeerisen merkkijonon vastaavaksi kokonaisluvuksi
// (kutsumalla stoi-funktiota).
// Jos annettu merkkijono ei ole numeerinen, palauttaa nollan.
//
// Converts the given numeric string to the corresponding integer
// (by calling stoi).
// If the given string is not numeric, returns zero.
unsigned int stoi_with_check(const string& str)
{
    bool is_numeric = true;
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        if(not isdigit(str.at(i)))
        {
            is_numeric = false;
            break;
        }
    }
    if(is_numeric)
    {
        return stoi(str);
    }
    else
    {
        return 0;
    }
}

// Tulostaa pelilaudan rivi- ja sarakenumeroineen.
//
// Prints the game board with row and column numbers.
void print(const vector< vector< int > >& gameboard)
{
    cout << "=================" << endl;
    cout << "|   | 1 2 3 4 5 |" << endl;
    cout << "-----------------" << endl;
    for(unsigned int i = 0; i < BOARD_SIDE; ++i)
    {
        cout << "| " << i + 1 << " | ";
        for(unsigned int j = 0; j < BOARD_SIDE; ++j)
        {
            if(gameboard.at(i).at(j) == 0)
            {
                cout << EMPTY << " ";
            }
            else
            {
                cout << gameboard.at(i).at(j) << " ";
            }
        }
        cout << "|" << endl;
    }
    cout << "=================" << endl;
}

vector<vector<int>> pelilaudan_luonti(vector< vector< int > >& gameboard){
// Luo pelilaudan halutulla tavalla.
// Voi itse päättää syöttääkö 25 numeroa vai antaako koneen arpoa 25 numeroa.
// Palauttaa vektorin, joka sisältää pelilaudan.
    string valinta;
    int seed;

    while (true) {

        cout << "Select start (R for random, I for input): ";
        getline(cin,valinta);

        // Satunnaisella valinnalla arvotut numerot
        if (valinta == "r" || valinta == "R"){
            cout << "Enter seed value: ";
            cin >> seed;
            default_random_engine gen(seed);
            uniform_int_distribution<int> distr(1, 5);
            vector<int> rivi;
            cin.clear();

            for (unsigned int i = 0; i < BOARD_SIDE; i++){
                for (unsigned int j = 0; j < BOARD_SIDE; j++){
                    rivi.push_back(distr(gen));
                }
                gameboard.push_back(rivi);
                rivi.clear();
            }
            return gameboard;

        // Käyttäjän syötteen numerot
        }else if (valinta == "i" || valinta == "I"){
            vector <int> numbers;
            string input;
            string str;

            cout << "Input: ";
            getline(cin, input);

            for (string::size_type i = 0; i < input.length(); i++){

                if (isdigit(input.at(i))){
                    str = input.at(i);
                    numbers.push_back(stoi_with_check(str));
                }
                if (numbers.size() == 5){
                    gameboard.push_back(numbers);
                    numbers.clear();
                }
            }
            return gameboard;
        }
    }

}
bool voiton_tarkastus(vector<vector<int>>& gameboard){
// Tarkastaa onko pelaaja voittanut
// eli testaa onko jokaisella sekä pysty että vaakarivillä
// vain yksi jokaista lukua 1-5
    string loydetyt_vaaka;
    string loydetyt_pysty;
    string::size_type kohta = 0;

    for (unsigned int i = 0; i < BOARD_SIDE; i++){
        for (unsigned int j = 0; j < BOARD_SIDE; j++){
            // Tarkastaa onko merkkijonossa arvoa.
            // Jos ei ole lisää sen merkkijonon, jos on niin ilmoittaa, että
            // peli on vielä kesken
            kohta = loydetyt_vaaka.find(gameboard.at(i).at(j));
            if (kohta == string::npos){
                if (gameboard.at(i).at(j) != 0){
                    loydetyt_vaaka += gameboard.at(i).at(j);
                }

            }else{
                return false;
            }
            // Tekee saman kuin äkseinen kohta, mutta sarakkeille.
            kohta = loydetyt_pysty.find(gameboard.at(j).at(i));
            if (kohta == string::npos){
                if (gameboard.at(j).at(i) != 0){
                    loydetyt_pysty += gameboard.at(j).at(i);
                }

            }else{
                return false;
            }
        }
        loydetyt_pysty.clear();
        loydetyt_vaaka.clear();

    }
    return true;
}

bool havion_testaus(vector<vector<int>>& gameboard){
// Testaa onko yksikään numero sellaisella paikalla, että peli loppuisi
// Testaa siis onko tyhjiä ruutuja vierekkäin tai onko yksikään numero ilman vieruskumppania.
    for (unsigned int i = 0; i < BOARD_SIDE; i++){
        for (unsigned int j = 0; j < BOARD_SIDE; j++){

            if (gameboard.at(i).at(j) !=0){
                if(i == 0 && j == 0){
                    if (gameboard.at(i+1).at(j) == 0 && gameboard.at(i).at(j + 1) == 0){
                        return true;
                    }
                }else if (i == 0 && j == BOARD_SIDE - 1){
                    if (gameboard.at(i + 1).at(j) == 0 && gameboard.at(i).at(j - 1) == 0){
                        return true;
                    }
                }else if(i == BOARD_SIDE - 1 && j == BOARD_SIDE - 1){
                    if (gameboard.at(i - 1).at(j) == 0 && gameboard.at(i).at(j - 1) == 0){
                        return true;
                    }
                }else if(i == BOARD_SIDE - 1 && j == 0){
                    if (gameboard.at(i - 1).at(j) == 0 && gameboard.at(i).at(j + 1) == 0){
                        return true;
                    }
                }else if (i != 0 && i != BOARD_SIDE - 1 && j != 0 && j != BOARD_SIDE - 1){
                    if (gameboard.at(i - 1).at(j) == 0 && gameboard.at(i).at(j + 1) == 0
                            && gameboard.at(i + 1).at(j) == 0 && gameboard.at(i).at(j - 1) == 0){
                        return true;
                    }
                }else if (i == 0 || i == BOARD_SIDE - 1){
                    if(i == 0){
                        if(gameboard.at(i + 1).at(j) == 0 && gameboard.at(i).at(j - 1) == 0 && gameboard.at(i).at(j + 1) == 0)
                            return true;
                    }else{
                        if(gameboard.at(i - 1).at(j) == 0 && gameboard.at(i).at(j - 1) == 0 && gameboard.at(i).at(j + 1) == 0)
                            return true;
                    }
                }else{
                    if(j == 0){
                        if(gameboard.at(i + 1).at(j) == 0 && gameboard.at(i).at(j + 1) == 0 && gameboard.at(i - 1).at(j) == 0)
                            return true;
                    }else{
                        if(gameboard.at(i - 1).at(j) == 0 && gameboard.at(i).at(j - 1) == 0 && gameboard.at(i + 1).at(j) == 0)
                            return true;
                    }
                }

            }else{
                if(i == 0 && j == 0){
                    if (gameboard.at(i+1).at(j) == 0 || gameboard.at(i).at(j + 1) == 0){
                        return true;
                    }
                }else if (i == 0 && j == BOARD_SIDE - 1){
                    if (gameboard.at(i + 1).at(j) == 0 || gameboard.at(i).at(j - 1) == 0){
                        return true;
                    }
                }else if(i == BOARD_SIDE - 1 && j == BOARD_SIDE - 1){
                    if (gameboard.at(i - 1).at(j) == 0 || gameboard.at(i).at(j - 1) == 0){
                        return true;
                    }
                }else if(i == BOARD_SIDE - 1 && j == 0){
                    if (gameboard.at(i - 1).at(j) == 0 || gameboard.at(i).at(j + 1) == 0){
                        return true;
                    }
                }else if (i != 0 && i != BOARD_SIDE - 1 && j != 0 && j != BOARD_SIDE - 1){
                    if (gameboard.at(i - 1).at(j) == 0 || gameboard.at(i).at(j + 1) == 0 ||
                            gameboard.at(i + 1).at(j) == 0 || gameboard.at(i).at(j - 1) == 0){
                        return true;
                    }
                }else if (i == 0 || i == BOARD_SIDE - 1){
                    if(i == 0){
                        if(gameboard.at(i + 1).at(j) == 0 || gameboard.at(i).at(j - 1) == 0 || gameboard.at(i).at(j + 1) == 0)
                            return true;
                    }else{
                        if(gameboard.at(i - 1).at(j) == 0 || gameboard.at(i).at(j - 1) == 0 || gameboard.at(i).at(j + 1) == 0)
                            return true;
                    }
                }else{
                    if(j == 0){
                        if(gameboard.at(i + 1).at(j) == 0 || gameboard.at(i).at(j + 1) == 0 || gameboard.at(i - 1).at(j) == 0)
                            return true;
                    }else{
                        if(gameboard.at(i - 1).at(j) == 0 || gameboard.at(i).at(j - 1) == 0 || gameboard.at(i + 1).at(j) == 0)
                            return true;
                    }
                }
            }

        }
    }
    return false;


}
void ruutujen_poistaminen(vector<vector<int>>& gameboard){
// Poistaa valittuja ruutuja syötettyjen x ja y koordinaattien perusteella.
// Tarkastaa onko koordinaatti edes mahdollinen ja jättää myös muut kuin numerot
// huomiotta.
    string x;
    string y;

    // kysyy käyttäjältä syötteitä kunnes tämä päättää lopettaa antamalla syötteeksi "Q"
    //tai peli loppuu häviöön/voittoon.
    while (true) {

        cout << "Enter removable element (x, y): ";
        cin >> x;

        if (x == "q" || x == "Q"){
            cout << "Quitting" << endl;
           return;
        }

        cin >> y;
        // Tarkastaa onko arvot int tyyppisiä, jos eivät
        // niin ilmoittaa virheellisestä syötteestä.
        // Ilmoittaa myös jos koordinaatit eivät ole taulukon sisällä.
        if (stoi_with_check(x) && stoi_with_check(y)){
            if (stoi_with_check(x) <= BOARD_SIDE && stoi_with_check(y) <= BOARD_SIDE){
                if (gameboard.at(stoi_with_check(y)-1).at(stoi_with_check(x)-1) == 0){
                    cout << "Already removed" << endl;
                }else{
                    gameboard.at(stoi_with_check(y)-1).at(stoi_with_check(x)-1) = 0;
                    print(gameboard);

                    //Tarkastaa onko peli voitettu
                    if (voiton_tarkastus(gameboard)){
                        cout << "You won" << endl;
                        break;
                    }
                    // Tarkastaa onko peli hävitty
                    if (havion_testaus(gameboard)){
                        cout << "You lost" << endl;
                        break;
                    }
                }
            }else{
                cout << "Out of board" << endl;
            }

        }else{
            cout << "Out of board" << endl;
        }
    }
}


int main()
{
    vector<vector<int>> gameboard;
    gameboard = pelilaudan_luonti(gameboard);


    print(gameboard);
    ruutujen_poistaminen(gameboard);


    return 0;
}
