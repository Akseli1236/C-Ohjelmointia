#include <iostream>

using namespace std;

int main()
{
    int number;
    cout << "Enter a number: ";
    cin >> number;


    if (number >= 0){
        int cube = number * number * number;
        int original = cube / number / number;
        if (number == original){
            cout << "The cube of " << number << " is " << cube << "." << endl;

        }else{
                cout << "Error! the cube of " << number << " is not " << cube << endl;

        }

    }
     return 0;
}
