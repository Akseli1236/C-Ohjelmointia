#include <cstdlib>
#include <iostream>
#include <vector>


void read_integers(std::vector< int >& ints, int count)
{
    int new_integer = 0;
    for(int i = 0; i < count; ++i)
    {
        std::cin >> new_integer;
        ints.push_back(new_integer);


        // TODO: Implement your solution here

    }
}

bool same_values(std::vector< int >& ints)
{
    int testi = ints.at(0);
    for (int alkio : ints)
    {
        if (testi != alkio){
            return false;
        }

    }
    return true;
}

bool is_ordered_non_strict_ascending(std::vector< int >& ints)
{
    int testi = ints.at(0);
    for (int alkio : ints)
    {
        if (testi <= alkio){
            testi = alkio;
        }else{
            return false;
        }

    }

    return true;
}

bool is_arithmetic_series(std::vector< int >& ints)
{
    int testi = ints.at(1) - ints.at(0);
    std::vector<int>::size_type i = 0;
    while (i < ints.size())
    {
        if (i + 1 != ints.size())
        {
            if (ints.at(i+1)-ints.at(i) != testi){
                return false;
            }
        }
        i++;

    }

    return true;
}

bool is_geometric_series(std::vector< int >& ints)
{

    std::vector<int>::size_type i = 0;
    if (ints.front() == 0 && ints.back() == 0){
        return false;
    }

    int testi = ints.at(1)/ints.at(0);
    while (i < ints.size())
    {


        if (i + 1 != ints.size())
        {
            if (ints.at(i+1)/ints.at(i) != testi){
                return false;
            }
        }
        i++;

    }

    return true;
}


// TODO: Implement your solution here


int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    if(same_values(integers))
        std::cout << "All the integers are the same" << std::endl;
    else
        std::cout << "All the integers are not the same" << std::endl;

    if(is_ordered_non_strict_ascending(integers))
        std::cout << "The integers are in a non-strict ascending order" << std::endl;
    else
        std::cout << "The integers are not in a non-strict ascending order" << std::endl;

    if(is_arithmetic_series(integers))
        std::cout << "The integers form an arithmetic series" << std::endl;
    else
        std::cout << "The integers do not form an arithmetic series" << std::endl;

    if(is_geometric_series(integers))
        std::cout << "The integers form a geometric series" << std::endl;
    else
        std::cout << "The integers do not form a geometric series" << std::endl;

    return EXIT_SUCCESS;
}
