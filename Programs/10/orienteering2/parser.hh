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



/*
#############################################################################
# COMP.CS.110 Ohjelmointi 2: Rakenteet / Programming 2: Structures          #
# Project3: Suunnistus / Orienteering                                       #
# File: parser.hh                                                           #
# Description: Module that parses the input file into an OrienteeringMap    #
#        object.                                                            #
# Notes: * This is a part of an exercise program.                           #
#        * Student's don't touch this file.                                 #
#        * Understanding how the module works isn't necessary to complete   #
#          this exercise.                                                   #
#############################################################################
*/

#ifndef PARSER_HH
#define PARSER_HH

#include "orienteeringmap.hh"
#include <memory>

bool read_input_from_file(std::string file,
                          std::shared_ptr<OrienteeringMap> routes);

#endif // PARSER_HH
