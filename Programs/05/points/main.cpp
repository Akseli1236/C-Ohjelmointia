#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    string input = "";
    cout << "Input file: ";
    getline(cin, input);
    ifstream input_olio(input);

    if (not input_olio){
        cout << "Error! The file " << input << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }

    string rivi;
    string nimi;
    string arvo;
    string::size_type kohta;
    map<string, double> pisteet;
    vector<string> kallu;
    while (getline(input_olio, rivi)) {
        kohta = rivi.find(":");
        nimi = rivi.substr(0, kohta);
        arvo = rivi.substr(kohta + 1);

        if (pisteet.find(nimi) != pisteet.end()){
            pisteet.at(nimi) += stoi(arvo);
        }else{
            pisteet.insert({nimi, stoi(arvo)});

        }

    }
    cout << "Final scores:" << endl;
    for (auto a: pisteet){
        cout << a.first << ": " << pisteet.at(a.first) << endl;
    }



    return 0;
}
