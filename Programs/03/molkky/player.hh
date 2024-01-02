#ifndef PLAYER_HH
#define PLAYER_HH
#include <string>

using namespace std;


class Player
{
public:
    Player();

    Player(string nimi, int points = 0);

    string get_name();
    void add_points(int points);
    int get_points() const;
    bool has_won();

private:
    string nimi_;
    int points_;
};

#endif // PLAYER_HH
