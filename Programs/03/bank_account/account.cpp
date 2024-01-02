#include "account.hh"
#include <iostream>


std::string iban_ = "";

Account::Account(const std::string& owner, bool has_credit, int money, int credit_limit):
  owner_(owner), has_credit_(has_credit), money_(money), credit_limit_(credit_limit){

    generate_iban();
}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{

    ++running_number_;
    std::string suffix = "";

    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);

}
void Account::save_money(int amount){
    money_ += amount;

}
void Account::set_credit_limit(int amount){
    if (has_credit_){
        credit_limit_ = amount;
    }else{
        std::cout << "Cannot set credit limit: the account has no credit card" << std::endl;
    }
}

void Account::take_money(int amount){
    if (credit_limit_ == 0){
        if (money_ < amount){
            std::cout << "Cannot take money: balance underflow" << std::endl;
        }else{
            money_ -= amount;
            std::cout << amount << " euros taken: new balance of " << iban_ << " is " << money_ << " euros" << std::endl;

        }
    }else{
        if(money_ + credit_limit_ < amount){
            std::cout << "Cannot take money: credit limit overflow" << std::endl;
        }else{
            money_ -= amount;
            std::cout << amount << " euros taken: new balance of " << iban_ << " is " << money_ << " euros" << std::endl;

        }
    }
}
void Account::transfer_to(Account& kohde, int amount){
    if (money_ + credit_limit_< amount){
        if (credit_limit_ == 0){
            std::cout << "Cannot take money: balance underflow" << std::endl;
        }else{
            std::cout << "Cannot take money: credit limit overflow" << std::endl;
        }

        std::cout << "Transfer from " << iban_ << " failed" << std::endl;
    }else{
        kohde.save_money(amount);
        money_ -= amount;
        std::cout << amount << " euros taken: new balance of " << iban_ << " is " << money_ << " euros" << std::endl;
    }

}

void Account::print() const{
    std::cout << owner_ << " : " << iban_ << " : " << money_ << " euros" << std::endl;
}
