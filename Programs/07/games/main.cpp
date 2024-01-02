/*  COMP.CS.100 Project 2: GAME STATISTICS
 * ===============================
 * EXAMPLE SOLUTION
 * ===============================
 *
 * Ohjelma on tietokanta peleille, joka tallentaa pelin, sitä pelaavat pelaajat ja heidän pisteensä.
 * Ohjelma toimii seuraavilla komennoilla.
 * All_games tulostaa jokaisen pelin, joka on tietokantaan tallennettu
 * Game <pelaajan nimi> Kertoo jokaisen pelin, jota tietty pelaaja on pelannut.
 * All_players tulostaa jokaisen pelaaja, joka on tietokannassa
 * Add_game lisää pelin
 * Add_player <Peli> <Pelaajan nimi> <pisteet> lisää pelaajan syötettyjen argumenttien perusteella
 * Mikäli pelaaja on jo tietokannassa tämän pisteet päivittyvät syötteen mukaan.
 * Remove_player poistaa halutun pelaajan. Tämä tarkoittaa sitä, että hänet poistetaan kaikista peleist,
 * joita hän on pelannut
 * Quit lopettaa ohjelman toiminnan
 *
 * Vääränlaisen syötteen tapauksessa ohjelma ilmoittaa tästä
 * Jos tiedostoa ei löydy tai tiedostossa olevat tiedot ovat väärässä muodossa ohjelman toteutus lakkaa.
 *
 *
 * Ohjelman kirjoittaja ( Täytä omilla tiedoillasi )
 * Nimi: Akseli Ahonen
 * Opiskelijanumero: 150313812
 * Käyttäjätunnus: tbakah ( Git-repositorion hakemistonimi. )
 * E-Mail: akseli.ahonen@tuni.fi
 *
 * Huomioita ohjelmasta ja sen toteutuksesta:
 * */


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <map>

using namespace std;
// Casual split func, if delim char is between "'s, ignores it.
std::vector<std::string> split( const std::string& str, char delim = ';' )
{
    std::vector<std::string> result = {""};
    bool inside_quatation = false;
    for ( auto current_char : str )
    {
        if ( current_char == '"' )
        {
            inside_quatation = not inside_quatation;
        }
        else if ( current_char == delim and not inside_quatation )
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(current_char);
        }
    }
    if ( result.back() == "" )
    {
        result.pop_back();
    }
    return result;
}

string input_cleaner(vector<string> parts){

    // Saa syötteen ja poistaa siitä mahdollisesti
    // ylimääräiset lainausmerkit, jos niitä on.
    // Saa argumenttina listan, joka sisältää syötteen.
    // Palauttaa puhdistetun syötteen

    string input;
    string input_stripped;

    //poistaa ensimmäisen sanan, koska se on komento
    //eikä sitä haluta käsitellä
    parts.erase(parts.begin(), parts.begin()+1);

    //Käy läpi syötteen sisältävän listan indeksi kerrallan
    //ja muuttaa listan merkkijonoksi
    for (const string& indx : parts){
        input += indx;
    }

    //Merkkaa missä kohdassa löytyy lainausmerkit jos löytyy
    //ja poistaa ne.
    int quote_start = input.find("\"");
    int quote_end = input.find_last_of("\"");
    input_stripped = input.substr(quote_start+1,quote_end-quote_start-1);

    return input_stripped;
}

map<string, map<int, vector<string>>> data_processing(map<string
                                                      , map<int, vector<string>>> all_data
                                                      , vector<string> splitted_line, int add_or_rem_player = 0){


    //Funktio Saa parametrina tietokannan, listan lisättävistä
    //syötteen parametreista ja tiedon mistä komennosta
    //on kyse add_or_rem_player argumenttiin


    //Funktio lisää pelaajia tietokantaan
    //ja tarkistaa missä tilanteessa lisäys tehdään.
    //Jos tietolisätään ensimmäistä kertaa,
    //mitään erityistätarvita.Mikäli funktiota kutsutaan
    //ADD_PLAYER tai REMOVE_PLAYER komennoilla niin kutsuun liitty
    //argumentti, joka varmistaa, ettälisäys tapahtuu oikein.
    //Funktio palauttaa tietokantaan lisätyn datan.

    string game;
    string name;
    int score;
    map<string, map<int, vector<string>>>::size_type found = 0;


    //Testaa onko argumenttina saadussa listassa kolme alkiota
    //jos ei ole niin tiedoston muoto on vääränlainen.
    if (splitted_line.size() != 3){
        all_data["Error"];
        return all_data;
    }else{
        //Pätkii listan, jotta alkiota voidaan käyttää
        game = splitted_line.at(0);
        name = splitted_line.at(1);
        score = stoi(splitted_line.at(2));

        //Tarkastaa onko kyseessä pelaajan toistaminen tai lisääminen.
        //Poistamisen ja lisäämisen tapauksessa argumenttina saadan luku,
        //joka kertoo mistä komennosta on kyse.
        //1 on pelaajan lisääminen ja 2 poistaminen. 0 tarkoittaa alussa
        //tapahtuvaa lisäämista
        if (add_or_rem_player != 0){

            //Käydään läpi kaikki pelit.
            for (const auto& points : all_data[game]){

                //Jos pelaaja on ainoana tietyssä pelissä tietyillä pisteillä
                //Voidaan suoraan poistaa tämä alkio
                if (count(points.second.begin(), points.second.end(), name)){
                    all_data[game][points.first].erase
                            (remove(all_data[game][points.first].begin()
                                        , all_data[game][points.first].end(), name)
                                        , all_data[game][points.first].end());

                    //Tarkastetaan samalla tavalla mikä komento on kyseessä
                    //Kuten aiemmin.
                    if (add_or_rem_player == 1){
                        all_data[game][score].push_back(name);
                    }

                    //Jos pisteisiin liityvä lista on tyhjä,
                    //niin se poistetaan kokonaan
                    if (all_data[game][points.first].size() == 0){
                        all_data[game].erase(points.first);
                    }

                    break;
                }else{
                    //Mikäli pelaajaa ei löytynyt tietyistä pisteitsä
                    //Niin se kirjataan ylös
                    found++;
                }

            }
        }else{
            all_data[game][score].push_back(name);
        }
    }

    //Tarkastetaan onko niin, että pelaajaa ei löytynyt ollenkaan
    //kyseisetä pelistä ADD_PLAYER-komentoa käyttäessä ja lisätään
    //Täysin uusi pelaaja, jos ei löytynyt
    if(found == all_data[game].size() && add_or_rem_player == 1){
        all_data[game][score].push_back(name);
    }
    return all_data;
}

map<string, map<int, vector<string>>> data(map<string
                   , map<int, vector<string>>> all_data, istream& filename){

    //Tämä funktio käy läpi tiedoston rivi kerrallaan
    //ja palauttaa kaiken datan, jonne ollaan lisätty
    //tiedoston tiedot.
    //Saa parametrina tietokannan ja tiedosto_olion

    string line;
    vector<string> splitted_line;

    while (getline(filename, line)){
        splitted_line = split(line);
        all_data = data_processing(all_data, splitted_line);
    }
    return all_data;
}


void prints_who_plays(map<string, map<int, vector<string>>> all_data, string game){
    //Tämä funktio tulostaa kaikki ketkä pelaavat tiettyä peliä
    //Saa parametrina tietokannan ja pelin nimen.

    cout << "Game " << game
         << " has these scores and players, listed in ascending order:" << endl;

    //Käydään läpi kaikki pelin pisteet
    for (const auto& game : all_data[game]){
        if (game.second.size() > 1){
            cout << game.first << " : ";
            //Käydään läpi ne nimet, jotka läytyvät
            //halutusta pelistä ja tulostetaan ne
            for (const string& names : game.second){
                if (game.second.back() == names){
                    cout << names;
                }else{
                    cout << names << ", ";
                }
            }
            cout << endl;
        }else{
            cout << game.first << " : " <<game.second.at(0) << endl;
        }
    }
}

void print_all_names(map<string, map<int, vector<string>>> all_data){
    //Tulostaa kaikkien pelaajien nimet, jotka löytyvät
    //tietokannasta. Saa parametrina tietokannan.


    cout << "All players in alphabetical order:" << endl;
    vector<string> names;

    //Käydään läpi kaikki pelit
    for (const auto& game : all_data){
        //Käydään läpi pisteet
        for (const auto& score : all_data[game.first]){
            for (const string& name : score.second){
                //jos nimi ei ole vielä esiintynyt se lisätään listaan
                if (not count(names.begin(), names.end(), name)){
                    names.push_back(name);
                }
            }
        }
    }
    //Järjestetään nimet aakkosjärjestykseen ja sitten tulostetaan
    sort(names.begin(), names.end());
    for (const auto& print : names){
        cout << print << endl;
    }
    names.clear();
}


vector<string> players_games(map<string, map<int, vector<string>>> all_data
                             , string player){

    vector<string> games;

    //Tässä funktiossa listataan vektoriin kaikki pelit
    //joita tietty pelaaja pelaa
    //Saa parametrina tietokannan ja pelaajan nimen
    //Tämä lista palautetaan vectorin.

    //Käydään läpi kaikki pelit
    for (const auto& game : all_data){
        //Käydään läpi kaikki pisteet
        for (const auto& score : all_data[game.first]){
            //Käydään läpi kaikki nimet
            for (const string& name : score.second){
                if (name == player){
                    games.push_back(game.first);
                }
            }
        }
    }
    return games;
}

map<string, map<int, vector<string>>>
remove_player(map<string, map<int, vector<string>>> all_data, string name){

    //Tämä Funktio poistaa datasta tietyn pelaajan
    //Ja tähän liittyvät pisteet jokaisesta pelistä.
    //Saa parametrina tietokannan ja poistettavan pelaajan nimen
    //Palauttaa datan kaikista pelaajista päivitettynä.

    //Saadaan listaan pelaajan pelaamat pelit
    vector<string> games = players_games(all_data, name);
    vector<string> player;

    //Käydään läpi kaikki pelit, joita pelaaja pelaa
    for (auto const& specific_game : games){

        //Lisätään listaan pelattu peli
        player.push_back(specific_game);

        //Käydään läpi kaikki tietyn pelin pisteet
        for (const auto& y : all_data[specific_game]){

            //jos pelaajalla oli pisteetiä tieytssä pelissä
            //niin tieto siitä lähetetään data_processing
            //funktiolle luku 2 argumenttina, joka tarkoittaa
            //pelaajan poistamita.
            if(count(y.second.begin(), y.second.end(), name)){
                string score = to_string(y.first);
                player.push_back(name);
                player.push_back(score);
                all_data = data_processing(all_data,player,2);

                break;
            }
        }
        player.clear();
    }
    games.clear();
    return all_data;

}


void split_string(string line, vector<string>& line_in_vector){

    //Tämän funktion tarkoitus on poistaa kaikki ylimääräiset
    //välilyönnit syötteestä ja lisätä jokainen parametri listaan
    //omana alkionaan.
    //Saa parametrina syöterivin ja vectorin,
    //jonne korjattu syöte lisätään

    string temp = "";

    //Käydään läpi argumenttina saatu merkkijono
    for(string::size_type i = 0; i < line.length();i++){

        //Jos löytyy lainausmerkkejä niiden sisältö
        //lisätään listaan.
        if (line[i]== '"'){
            while(true){
                i++;
                if(line[i]== '"'){
                    break;
                }
                temp.push_back(line[i]);
            }
            i++;
            line_in_vector.push_back(temp);
            temp= "";

        //Välilyöntien kohdalla listaan lisätään alkio, joka
        //muodostui väliaikaiseen merkkijonoon.
        }else if(line[i]==' '){
            line_in_vector.push_back(temp);
            temp = "";
        }else{
            temp.push_back(line[i]);
        }
    }
    line_in_vector.push_back(temp);
}

int main()
{
    //Main testaa onko tiedosto oikean niminen ja onko se oikeassa muodossa.
    //Main myös kysyy käyttäjältä komentoja.

    string filename;
    map<string, map<int, vector<string>>> all_data;
    cout << "Give a name for input file: ";
    getline(cin,filename);

    //Testataan onnistuiko tidosto_olion luominen, jos ei niin
    //oikean nimistä tiedostoa ei annettu
    ifstream file_object(filename);
    if (not file_object){
        cout << "Error: File could not be read." << endl;
        return EXIT_FAILURE;
    }else{
        //Tässä vaiheessa testataan onko tiedosto oikeanlainen.
        all_data = data(all_data, file_object);
        if (all_data.find("Error") != all_data.end()){
            cout << "Error: Invalid format in file." << endl;
            return EXIT_FAILURE;
        }
    }
    file_object.close();


    while (true) {

        string command;
        vector<string> parts;
        cout << "games> ";
        getline(cin,command);

        //Muodostetaan syötteestä lista.
        split_string(command, parts);

        //Muutetaan komento isoiksi kirjaimiksi
        for_each(parts.at(0).begin(), parts.at(0).end(), [](char & c){
            c = toupper(c);
        });

        //Tässä vaiheessa luetaan syötteitä ja suoritetaan haluttuja
        //komentoja
        if (parts.at(0) == "QUIT"){
            break;
        }else if (parts.at(0) == "ALL_GAMES"){
            cout << "All games in alphabetical order:" << endl;
            for (const auto& name : all_data){
                cout << name.first << endl;
            }
        }else if(parts.at(0) == "GAME"){

            string game_stripped = input_cleaner(parts);


            if (game_stripped.find_first_not_of(" ") == string::npos){
                cout << "Error: Invalid input." << endl;
            }else if (all_data.find(game_stripped) == all_data.end()){
                cout << "Error: Game could not be found." << endl;
            }else{
                prints_who_plays(all_data, game_stripped);

            }


        }else if(parts.at(0) == "ALL_PLAYERS"){
            print_all_names(all_data);

        }else if(parts.at(0) == "PLAYER"){

            string player_stripped = input_cleaner(parts);


            if (player_stripped.find_first_not_of(" ") == string::npos){
                cout << "Error: Invalid input." << endl;
            }else{
                vector<string>games = players_games(all_data, player_stripped);
                sort(games.begin(), games.end());
                if (games.size() == 0){
                    cout << "Error: Player could not be found." << endl;
                }else{
                    cout << "Player " << player_stripped << " playes the following games:" << endl;
                    for (const string& name_of_the_game : games){
                            cout << name_of_the_game << endl;
                        }
                }
                games.clear();
            }


        }else if (parts.at(0) == "ADD_GAME"){
            string add_game = input_cleaner(parts);

            if (add_game.find_first_not_of(" ") == string::npos){
                cout << "Error: Invalid input." << endl;
            }else{
                if (all_data.find(add_game) == all_data.end()){
                    cout << "Game was added." << endl;
                    all_data[add_game];
                }else{
                    cout << "Error: Already exists." << endl;
                }
            }

        }else if (parts.at(0) == "ADD_PLAYER"){

            parts.erase(parts.begin(), parts.begin()+1);

            if (parts.size() != 3){
                cout << "Error: Invalid input." << endl;
            }else if (all_data.find(parts.at(0)) != all_data.end()){
                cout << "Player was added." << endl;
                all_data = data_processing(all_data,parts, 1);
            }else{
                cout << "Error: Game could not be found." << endl;
            }

        }else if(parts.at(0) == "REMOVE") {
            string removed = input_cleaner(parts);

            if (removed.find_first_not_of(" ") == string::npos){
                cout << "Error: Invalid input." << endl;
            }else if (players_games(all_data,removed).size() == 0){
                cout << "Error: Player could not be found." << endl;
            }else{
                cout << "Player was removed from all games." << endl;
                all_data = remove_player(all_data,removed);
            }
        }else{
            cout << "Error: Invalid input." << endl;

        }
    }

    return EXIT_SUCCESS;
}
