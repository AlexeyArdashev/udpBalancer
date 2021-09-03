#include <iostream>

#include "balancer.hpp"

using namespace std;

int main()
{
    cout <<"***** START WORKIN UDP BALANCER *****" << endl;
   try
    {
    Balancer balancer;
    balancer.start();
    }
    catch (std::exception& er) {
        cout << er.what()<< endl;
    }
    return 0;
}
