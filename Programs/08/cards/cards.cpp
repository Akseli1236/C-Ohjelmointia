#include "cards.hh"
#include <iostream>

using namespace std;

// TODO: Implement the methods here

Cards::Cards(): top_(nullptr){

}

Card_data *Cards::get_topmost()
{

    return top_;
}

Cards::~Cards(){
    while (top_ != nullptr) {
        Card_data* release = top_;
        top_ = top_->next;

        delete release;
    }
}

void Cards::add(int id){
    Card_data* temp = new Card_data{id, nullptr};
    temp->next = top_;
    top_ = temp;

}

bool Cards::remove(int& id){
    if (top_ == nullptr){
        return false;
    }

    Card_data* tempor = top_;
    id = tempor->data;

    top_ = tempor->next;
    delete tempor;

    return true;

}

void Cards::print_from_top_to_bottom(ostream& s){

     if(top_ != nullptr){

        Card_data* print = top_;
        int running_number = 1;

        while (print != nullptr) {

           s << running_number<< ": " << print->data << endl;
           running_number++;
           print = print->next;
        }
    }
}


bool Cards::bottom_to_top(){

    if (top_ != nullptr){

        Card_data* temp = top_;

        if (temp->next != nullptr){
            while (true) {
                if (temp->next->next == nullptr){
                    break;
                }
                temp = temp->next;
            }

            Card_data* temp2 = temp->next;
            temp->next = temp2->next;
            Card_data* temp3 = new Card_data{temp2->data, nullptr};

            delete temp2;


            temp3->next = top_;
            top_ = temp3;
        }



        return true;
    }else{
        return false;
    }

}

bool Cards::top_to_bottom(){

     if (top_ != nullptr){
        Card_data* temp = top_;

        if (temp->next != nullptr){
            top_ = temp->next;
            Card_data* temp2 = new Card_data{temp->data, nullptr};
            delete temp;
            Card_data* temp3 = top_;

            if (temp3 != nullptr){

                while (temp3->next != nullptr){
                    temp3 =temp3->next;
                }
                temp3->next = temp2;
            }
        }

        return true;
     }else{
         return false;
     }
}

void Cards::print_from_bottom_to_top(std::ostream& s){
        if (top_ != nullptr){
            Card_data* current = top_;
            Card_data* prev = {};
            Card_data* next = {};

            while (current != nullptr) {
                next = current->next;
                current->next = prev;
                prev = current;
                current = next;
            }
            top_ = prev;

            Card_data* temp = top_;
            int running_number = 1;
            while (temp != nullptr) {
                s << running_number << ": " << temp->data << endl;
                running_number++;
                temp = temp->next;
            }

            current = top_;
            prev = nullptr;
            next = nullptr;
            while (current != nullptr) {
                next = current->next;
                current->next = prev;
                prev = current;
                current = next;
            }
            top_ = prev;
       }

}


