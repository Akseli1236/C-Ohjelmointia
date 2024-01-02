#include <iostream>
#include <string>

using namespace std;

int main(){

    int temp;
    cout << "Enter a temperature: ";
    cin >> temp;

    cout << temp << " degrees Celsius is " << temp * 1.8 + 32 << " degrees Fahrenheit" << endl;
    cout << temp << " degrees Fahrenheit is " << (temp - 32) / 1.8 << " degrees Celsius" << endl;

    // Write your code here

    return 0;
}
