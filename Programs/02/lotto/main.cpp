#include <iostream>

using namespace std;

unsigned long int fact(unsigned long int arvo){
    unsigned long int i;
    unsigned long int factorial = 1;

    for(i = 2;i<=arvo;i++){
        factorial = factorial * i;

    }
    return factorial;

}

int main()
{

    cout << "Enter the total number of lottery balls: ";
    int kokonaismaara;
    cin >> kokonaismaara;

    cout << "Enter the number of drawn balls: ";
    int arvottavat;
    cin >> arvottavat;

    if (kokonaismaara > 0){
        if (arvottavat <= kokonaismaara){
            unsigned long int a = kokonaismaara - arvottavat;
            unsigned long int total = fact(kokonaismaara)/(fact(a)*fact(arvottavat));

            cout << "The probability of guessing all " << arvottavat << " balls correctly is " << "1/"<< total << endl;

        }else
            cout << "The maximum number of drawn balls is the total amount of balls." << endl;
    }else{
        cout << "The number of balls must be a positive number." << endl;
    }

    return 0;
}

