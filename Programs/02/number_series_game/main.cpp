#include <iostream>

using namespace std;

int main()
{
    int amount;
    int i = 1;
    std::cout << "How many numbers would you like to have? ";
    std::cin >> amount;

    while (i <= amount){
        if (i % 3 == 0 and i % 7 == 0){
            cout << "zip boing" << endl;
        }else if (i % 3 == 0){
            cout << "zip" << endl;

        }else if (i % 7 == 0){
            std::cout << "boing" << endl;

        }else{
            cout << i << endl;
        }
        i++;
    }
    cout << "I did a mistake so..." << endl;


    return 0;
}
