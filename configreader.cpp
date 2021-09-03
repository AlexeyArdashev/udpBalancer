
#include "configreader.hpp"
#include "exeptions.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>


using std::string;
using std::map;
using std::vector;
using std::pair;
using std::cout;

const string IP = "ip";
const string PORT = "port";
const string NODE = "node";
const string COUNT_NODE = "count_nodes";
const string LIMIT = "limit";

/*
 * проверка корректности файла конфигурации выполнена не полностью
 *
*/

uint32_t getIntIpAddr ( const string& ip ) {
    uint32_t rezult = 0;
    std::stringstream s( ip );
    int a, b, c, d;
    char ch;
    s >> a >> ch >> b >> ch >> c >> ch >> d;
    // std::cout << a << "  " << b << "  " << c << "  "<< d;
    rezult += ( (uint32_t) a << 24);
    rezult += ((uint32_t) b << 16);
    rezult += ((uint32_t) c << 8);
    rezult += (uint32_t)d;
    return rezult;
}

pair<string, string> split ( const string &s, const char delim ) {

    pair <string, string> rezult;
    auto pos = s.find(delim);
    if ( pos == std::string::npos
         || pos == s.size() -1 )
    {
        string msg ="bad string: ";
        msg += s;
        throw ConfigFileException(msg);
    }
    rezult.first =  s.substr( 0, s.find(delim) );
    rezult.second = s.substr( s.find(delim) + 1, s.size() - 1 );
    return rezult;
}

ConfigReader::ConfigReader( const string& nameFile )
{
    std::ifstream fin( nameFile );
    if ( !fin.is_open() ) {
        string msg;
        msg += "Config file '";
        msg += nameFile;
        msg += "'";
        msg += " not open";
        throw std::runtime_error(msg);
    }
    string line;
    std::map<string ,string> mapFile;

    while ( std::getline( fin, line ) ) {
        if ( line.empty() ) continue;
        auto key_value = split ( line, '=' );
        if ( mapFile.count( key_value.first) == 0 ) {
            mapFile [key_value.first] =  key_value.second;
        }
    }
    initSettingBalancer ( mapFile );
    initNodesConfig ( mapFile );

}

uint32_t ConfigReader::getIpBalancer() const
{
    return _networkBalancer.ipAddrInt;
}

uint16_t ConfigReader::getPortBalancer() const
{
    return _networkBalancer.port;
}

size_t ConfigReader::getCountNodes() const
{
    return _paramNodes.size();
}

const NetInfo &ConfigReader::ConfigReader::getNetInfoOfNode(size_t index) const
{
    return _paramNodes.at(index);
}

int ConfigReader::getLimitDatagram() const
{
    return _limitDatagramm;
}
void ConfigReader::initSettingBalancer( const std::map<std::string, std::string> &configFromFile )
{
    vector <string> settingBalancer = { IP, PORT, COUNT_NODE, LIMIT };

    for ( const string& key : settingBalancer ) {
        auto itMap = configFromFile.find( key );
        if ( itMap == configFromFile.end() ) {

            throw std::runtime_error ("missing key:" + key);
        }
        if ( key == IP ){
            _networkBalancer.ipAddrInt = getIntIpAddr ( itMap->second );
        }
        else if ( key == PORT ) {
            _networkBalancer.port = std::stoi ( itMap->second);
        }
        else if ( key == COUNT_NODE ) {
            size_t sizeVec = std::stoi ( itMap->second);
            _paramNodes.resize( sizeVec );
        }
        else if ( key == LIMIT ) {
            _limitDatagramm =  std::stoi ( itMap->second);
        }
    }
}

void ConfigReader::initNodesConfig( const std::map<std::string, std::string> &configFromFile )
{
    for ( size_t i = 0; i < _paramNodes.size(); i++ ) {
        string builded_ip = ( NODE + std::to_string(i+1) + "_" + IP);
        string builded_port = ( NODE + std::to_string(i+1) + "_" + PORT );

        auto ipIt = configFromFile.find(builded_ip);
        auto portIt = configFromFile.find( builded_port );

        if ( ipIt != configFromFile.end() &&
             portIt != configFromFile.end() )
        {
            _paramNodes[i].ipAddrInt = getIntIpAddr ( ipIt->second );
            _paramNodes[i].port = std::stoi ( portIt->second);;
        }
        else if ( ipIt ==  configFromFile.end() ) {
            throw std::runtime_error("missing key: " + builded_ip);
        }
        else
            throw std::runtime_error("missing key: " + builded_port);
    }
}

