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



#include "route.hh"
#include <iostream>
#include <algorithm>

Route::Route(){

}

Route::Route(std::string name, int x, int y, int height, char marker):
  //Luodaan rasti-olio parametrien avulla
  //Parametreina saadaan rastin nimi, x- ja y-koordinaatit, korkeuden
  //karttamerkin
  name_(name),x_(x), y_(y), height_(height), marker_(marker)

{}

std::string Route::getName() const
{
    //Palauttaa nimen
    return name_;
}

int Route::getx() const
{
    //Palauttaa x-koordinaatin
    return x_;

}

int Route::gety() const
{
    //Palauttaa y-koordinaatin
    return y_;
}

int Route::getHeight() const
{
    //Palauttaa Korkeuden
    return height_;
}

char Route::getMarker() const
{
    //Palauttaa karttamerkin
    return marker_;
}



