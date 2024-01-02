#include <iostream>
#include <string>
#include <vector>


// TODO: Implement split function here
// Do not change main function

std::vector<std::string> split(std::string line, char separator, bool lines=false)
{
    std::vector<std::string> lista;

    std::string::size_type i = 0;
    std::string kirjain = "";
    while (i < line.size()) {
        if (line.at(i) != separator){
            kirjain += line.at(i);

        }else{
            if(lines){
                if (i < line.size() - 1 && i > 0){
                    if (line.at(i + 1) != separator){
                        kirjain += "\n";
                    }
                }

            }else{
                kirjain += "\n";
            }
        }
        i++;
    }
    int a = kirjain.find("\n");
    if (a == 0 && lines){
        kirjain.erase(0,1);
    }


    lista.push_back(kirjain);
    return lista;
}


int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
