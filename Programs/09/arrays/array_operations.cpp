#include "array_operations.hh"
#include <string>
#include <iostream>

using namespace std;

int greatest_v1(int *itemptr, int size)
{
    int* osoitin = itemptr;
    int suurin = *itemptr;

    while (osoitin < itemptr + size) {
        if (*osoitin > suurin && *osoitin != 0){
            suurin = *osoitin;
        }
        ++osoitin;
    }
    return suurin;

}

int greatest_v2(int *itemptr, int *endptr)
{
    int* osoitin = itemptr;
    int suurin = *itemptr;

    while (osoitin < endptr) {

        if (*osoitin > suurin && *osoitin != 0){
            suurin = *osoitin;
        }
        ++osoitin;
    }
    return suurin;

}

void copy(int *itemptr, int *endptr, int *targetptr)
{
    if (itemptr != nullptr){
        int* osoitin = itemptr;

        while (osoitin < endptr) {
            *targetptr = *osoitin;
            targetptr++;
            osoitin++;

        }
    }


}

void reverse(int *leftptr, int *rightptr)
{

    int size = sizeof(*rightptr)/2;
    int i = 0;
    int temp = 0;
    rightptr--;

    while (i < size) {
        temp = *leftptr;
        *leftptr = *rightptr;
        *rightptr = temp;

        --rightptr;
        ++leftptr;

        i++;
    }

}
