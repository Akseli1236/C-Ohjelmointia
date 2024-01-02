#include "queue.hh"
#include "iostream"

// Implement the member functions of Queue here
using namespace std;

Queue::Queue(unsigned int cycle): first_(nullptr), last_(nullptr)
{
    cycle_ = cycle;
}

Queue::~Queue()
{
    while (first_ != nullptr){
        Vehicle* poista = first_;
        first_ = first_->next;

        delete poista;
    }

}

void Queue::enqueue(const string &reg)
{

    if (is_green_){
        cout << "GREEN: The vehicle " << reg << " need not stop to wait" << endl;
    }else{
        Vehicle* new_car = new Vehicle{reg, nullptr};
        if (first_ == nullptr){
            first_ = new_car;
        }else{
            Vehicle* temp = first_;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next =new_car;
        }
    }


}

void Queue::switch_light()
{
    if (is_green_){
        is_green_ = false;
        print();
    }else{
        is_green_ = true;
        print();

        unsigned int n = 0;
        while (first_ != nullptr && n < cycle_) {
              Vehicle* poista = first_;
              first_ = first_->next;
              delete poista;
              n++;
        }
        if (n != 0){
            is_green_ = false;
        }

    }




}

void Queue::reset_cycle(unsigned int cycle)
{
    cycle_ = cycle;

}

void Queue::print() const
{
     if(first_ != nullptr){

        Vehicle* print = first_;
        if (is_green_){
            cout << "GREEN: Vehicle(s) ";
            unsigned int n = 0;
            while (print != nullptr && n < cycle_) {
                cout << print->reg_num << " ";
                print = print->next;
                n++;
            }
            cout << "can go on" << endl;
        }else{
            cout << "RED: Vehicle(s) ";
            while (print != nullptr) {
                cout << print->reg_num << " ";
                print = print->next;
            }
            cout << "waiting in traffic lights" << endl;
        }




    }else{
         if (is_green_){
             cout << "GREEN: No vehicles waiting in traffic lights" << endl;
         }else{
             cout << "RED: No vehicles waiting in traffic lights" << endl;
         }

     }
}


