#include "book.hh"
#include <iostream>
#include <string>
#include "date.hh"

using namespace std;

Book::Book(string kirjailija, string nimi, bool lainattu):
    kirjailija_(kirjailija), nimi_(nimi), lainattu_(lainattu)
{

}

Book::~Book(){
}
Date lainattu;
Date exp_date;
void Book::loan(Date& lainaus){
    if (not lainattu_){
        lainattu_ = true;
        lainattu = lainaus;
        exp_date = lainaus;
        exp_date.advance(28);
    }else{
        cout << "Already loaned: cannot be loaned" << endl;

    }
}
void Book::renew(){
    if (lainattu_){
        exp_date.advance(28);
    }else{
        cout << "Not loaned: cannot be renewed" << endl;
    }


}

void Book::give_back(){
    lainattu_ = false;
}

void Book::print(){
    cout << kirjailija_ << " : " << nimi_ << endl;
    if (not lainattu_){
        cout << "- available" << endl;
    }else{
        cout << "- loaned: ";
        lainattu.print();
        cout << "- to be returned: ";
        exp_date.print();
    }
}
