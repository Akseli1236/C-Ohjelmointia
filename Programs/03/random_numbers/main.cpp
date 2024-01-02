#include <iostream>
#include <random>
#include <string>

using namespace std;

void produce_random_numbers(unsigned int lower, unsigned int upper, unsigned int seed_value)
{
    string kirjain;
    default_random_engine gen(seed_value);
    uniform_int_distribution<int> distr(lower, upper);
    cout << endl;



    while (kirjain !="q"){
        cout << "Your drawn random number is " << distr(gen) << endl;
        cout << "Press q to quit or any other key to continue: ";

        cin >> kirjain;
        cout << endl;

    }

}

int main()
{
    unsigned int lower_bound, upper_bound, seed_value;
    string kirjain = "";
    cout << "Enter a lower bound: ";
    cin >> lower_bound;
    cout << "Enter an upper bound: ";
    cin >> upper_bound;


    if(lower_bound >= upper_bound)
    {
        cout << "The upper bound must be strictly greater than the lower bound"
             << endl;
        return EXIT_FAILURE;
    }
    cout << "Enter a seed value: ";
    cin >> seed_value;
    produce_random_numbers(lower_bound, upper_bound, seed_value);



    return EXIT_SUCCESS;
}
