#include <iostream>

using namespace std;

int main()
{
    int number;
    cout << "Enter a positive number: ";
    cin >> number;
    int tester = 1;
    int first = 1;
    int erotus = number / first;
    int second;

    if (number > 0){
        while (tester <= number){
            second = number / tester;
            if (number % tester == 0){
                if (second / tester < erotus and second / tester >= 1){
                    erotus = second / tester;
                    first = tester;
                }
            }
            tester++;

        }
        second = number / first;
        cout << number << " = " << first << " * " << second << endl;
    }else{
        cout << "Only positive numbers accepted" << endl;
    }



    return 0;
}
