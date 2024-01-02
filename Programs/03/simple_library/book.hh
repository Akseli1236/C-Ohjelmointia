#ifndef BOOK_HH
#define BOOK_HH
#include "date.hh"

#include <string>

using namespace std;

class Book
{
public:
    Book(string kirjailija, string nimi, bool lainattu = false);
    ~Book();

    void loan(Date& lainaus);
    void renew();
    void print();
    void give_back();


private:
    string kirjailija_;
    string nimi_;
    bool lainattu_;



};





#endif // BOOK_HH
