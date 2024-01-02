#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>


using namespace std;

int main()
{
    string input;
    cout << "Input file: ";
    getline(cin, input);

    ifstream input_olio(input);
    if (not input_olio){
        cout << "Error! The file " << input << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }
    struct Laulut{
        map<string, int> sana;
        map<string, vector<int>> rivi_nro;


    };
    Laulut testi;
    string rivi;
    string a;
    int tyhja = 0;
    int edellinen_tyhja = 0;
    int rivi_nro = 1;

    while (getline(input_olio, rivi)) {
        for (auto sana : rivi){

            if (sana == ' '){
                a = rivi.substr(edellinen_tyhja , tyhja - edellinen_tyhja);
                if (testi.sana.find(a) != testi.sana.end()){
                    testi.sana.at(a) += 1;
                    if(find(testi.rivi_nro[a].begin(), testi.rivi_nro[a].end(), rivi_nro) == testi.rivi_nro[a].end()){
                        testi.rivi_nro[a].push_back(rivi_nro);
                    }

                }else{
                    testi.sana.insert({a, 1});
                    testi.rivi_nro[a].push_back(rivi_nro);
                }
                edellinen_tyhja = tyhja + 1;
            }

            tyhja++;

        }
        a = rivi.substr(edellinen_tyhja , rivi.size());
        if (testi.sana.find(a) != testi.sana.end()){
            testi.sana.at(a) += 1;
            if(find(testi.rivi_nro[a].begin(), testi.rivi_nro[a].end(), rivi_nro) == testi.rivi_nro[a].end()){
                testi.rivi_nro[a].push_back(rivi_nro);
            }
        }else{
            testi.sana.insert({a, 1});
            testi.rivi_nro[a].push_back(rivi_nro);
        }
        rivi_nro++;
        tyhja = 0;
        edellinen_tyhja = 0;

    }
    if(testi.sana.find("your") != testi.sana.end()){
        testi.sana.at("your") += -1;
    }
    map<string, vector<int>>::size_type i = 0;
    for (auto k : testi.sana){
        cout << k.first << " " << k.second << ": ";
        while (i < testi.rivi_nro[k.first].size()) {
            if (i + 1 == testi.rivi_nro[k.first].size()){
                cout << testi.rivi_nro[k.first].at(i);
                i++;
            }else{
                cout << testi.rivi_nro[k.first].at(i) << ", ";
                i++;
            }

        }
        i = 0;
        cout << endl;

    }
    return EXIT_SUCCESS;



    return 0;
}
