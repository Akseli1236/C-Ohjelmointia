/* COMP.CS.110 Ohjelmointi 2: Rakenteet / Programming 2: Structures
* Project3: Suunnistus / Orienteering

* Kuvaus
*   Ohjelma toteuttaa suunnistus kartan. Kartan voi tulostaa,
* siinä olevia reittejä ja rasteja voi tulostaa sekä tarkastella
* reittien pituuksia ja suurinta nousua tietystä pisteestä, jolloin
* ohjelma palauttaa kaikki ne reiti joilla on suurin nousu.
* Rastien, reittien ja kartan tiedot luetaan tekstitiedostosta.
* Virheellisen tiedoston yhteydessä suoritus keskeytyy
* samoin, jos tiedostoa ei löydy.
*
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
#include "parser.hh"
#include "cli.hh"
#include <iostream>



int main()
{
    std::shared_ptr<OrienteeringMap> routes(new OrienteeringMap);
    std::cout << "Input> ";
    std::string input;
    getline(std::cin, input);
    if( not read_input_from_file(input, routes) )
    {
        return EXIT_FAILURE;
    }
    Cli cli(routes);
    while( cli.exec_prompt() ){ }
    return EXIT_SUCCESS;
}


