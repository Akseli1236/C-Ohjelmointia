#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    string input = "";
    string output = "";
    string rivi = "";
    int rivi_numero = 1;

    cout << "Input file: ";
    getline(cin, input);
    cout << "Output file: ";
    getline(cin, output);


    ifstream input_olio(input);
    if (not input_olio){
        cout << "Error! The file " << input << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }
    ofstream output_olio(output);
    while (getline(input_olio, rivi)){
        output_olio << rivi_numero << " " << rivi << "\n";
        rivi_numero++;
    }

    input_olio.close();
    output_olio.close();


    return 0;
}
