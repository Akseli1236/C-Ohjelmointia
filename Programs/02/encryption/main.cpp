#include <iostream>

using namespace std;

int main()
{
    string key = "";
    string text = "";
    string korvaus = "";
    int encryption;
    string::size_type kohta = 0;
    int place;

    cout << "Enter the encryption key: ";
    getline(cin, key);

    if (key.length() != 26){
        cout << "Error! The encryption key must contain 26 characters." << endl;
        return EXIT_FAILURE;
    }else{
        for (int kirjain = 0; kirjain < 26; ++kirjain){
            if (isupper(key.at(kirjain))){
                cout << "Error! The encryption must contain only lower case characters." << endl;
                return EXIT_FAILURE;
            }
        }
        for (char kirjain = 'a'; kirjain <= 'z'; ++kirjain){
            kohta = key.find(kirjain);
            if (kohta == string::npos){
                cout << "Error! The encryption key must contain all alphabets a-z." << endl;
                return EXIT_FAILURE;
            }
        }
    }


    cout << "Enter the text to be encrypted: ";
    getline(cin,text);

    place = text.length();

    for (char kirjain= 0; kirjain < place; ++kirjain){
        if (isupper(text.at(kirjain))){
            cout << "Error! The text to be encrypted must contain only lower case characters." << endl;
            return EXIT_FAILURE;

        }else{
            encryption = char(text.at(kirjain))-97;
            korvaus = key.at(encryption);
            text.replace(kirjain, 1, korvaus);
        }
    }

    cout << "Encrypted text: " << text << endl;


    return 0;
}
