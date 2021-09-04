#include "balancer.hpp"

#include <iostream>
#include <algorithm>

using namespace std;

class CommandLineParcer {
public:
    CommandLineParcer ( int& argc, char** argv ) {
        for ( size_t i = 1; i < argc; i++ ) {
            tokens.push_back(string (argv[i]));
        }
    }
    bool cmdOptionExists( const string& option ) const{
        return find( tokens.begin(), tokens.end(), option )
                != this->tokens.end();
    }
    const string& getCmdOption( const string& option) const{
        auto itr =  find(tokens.begin(), tokens.end(), option );
        if (itr != tokens.end() && ++itr != tokens.end()){
            return *itr;
        }
        static const string empty_string("");
        return empty_string;
    }
private:
    vector <string> tokens;
};

int main( int argc, char **argv )
{
    cout <<"***** START WORKIN UDP BALANCER *****" << endl;
    CommandLineParcer parcer(argc, argv);
    try
    {
        Balancer balancer (parcer.getCmdOption("-f"));
        balancer.start();
    }
    catch (std::exception& er) {
        cout << er.what()<< endl;
    }
    return 0;
}
