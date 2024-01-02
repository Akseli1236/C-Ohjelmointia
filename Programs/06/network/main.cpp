#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";

int av = 0;
std::vector<std::string> split(const std::string& s,
                               const char delimiter,
                               bool ignore_empty = false)
{
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}
void print(map<string, vector<string>>& k, string id, string pisteet){
    for (auto nimi : k[id]){
        if (nimi == "T" || nimi == "R"){
            cout << pisteet + ".." << nimi << endl;
        }else{
            cout << pisteet << nimi << endl;
        }

        if (k.find(nimi) != k.end()){

            print(k,nimi, pisteet += "..");


        }
        pisteet.erase(0,2);
    }

}
unsigned int aliverkosto_lkm(map<string, vector<string>>&k, string id, unsigned int maara = 0){
   if (k.find(id) != k.end()){
       for (auto nimi : k[id]){
       maara += 1;
           if (k.find(nimi) != k.end()){
               //cout << maara <<"ennen"<< endl;
               return aliverkosto_lkm(k,nimi,maara);

            }
    }
   }
    return maara;
}

unsigned int aliverkosto_syvyys(map<string, vector<string>>& palkatut, string id2, unsigned int largest = 0){
    if (palkatut.find(id2) != palkatut.end()){
        for (auto nimi : palkatut[id2]){
        largest += 1;
            if (palkatut.find(nimi) != palkatut.end()){
                //cout << maara <<"ennen"<< endl;
                return aliverkosto_lkm(palkatut,nimi,largest) + 1;

             }
     }
    }
    return largest + 1;
}

unsigned int lkm(map<string, vector<string>>&k, string id, unsigned int maara){
    for (const auto& x : k[id]){
        maara = lkm(k,x,maara+1);

    }
    return maara;
}


int main()
{
    // TODO: Implement the datastructure here
    map<string, vector<string>> palkatut;
    string pisteet = "..";


    while(true)
    {

        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        // Allowing empty inputs
        if(parts.size() == 0)
        {
            continue;
        }

        std::string command = parts.at(0);

        if(command == "S" or command == "s")
        {
            if(parts.size() != 3)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            // TODO: Implement the command here!
            palkatut[id1].push_back(id2);


        }
        else if(command == "P" or command == "p")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            cout << id << endl;
            print(palkatut,id,pisteet);


        }
        else if(command == "C" or command == "c")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!

            cout << lkm(palkatut,id,0) << endl;

        }
        else if(command == "D" or command == "d")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            cout << aliverkosto_syvyys(palkatut,id) << endl;

        }
        else if(command == "Q" or command == "q")
        {
           return EXIT_SUCCESS;
        }
        else
        {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
