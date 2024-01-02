#include "player.hh"
#include <iostream>
#include <string>

Player::Player():
    nimi_(""), points_(0)
{

}

Player::Player(string nimi, int points):
    nimi_(nimi), points_(points)
{

}

string Player::get_name(){
    return nimi_;
}

void Player::add_points(int points){
    points_ += points;
    if (points_ > 50){
        points_ = 25;
        cout << nimi_ << " gets penalty points!" << endl;
    }
}

int Player::get_points() const{
    return points_;
}

bool Player::has_won(){
    if (points_ == 50){
        return true;
    }else{
        return false;
    }
}
