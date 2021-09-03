#pragma once

#include <string>
#include <map>
#include <vector>

struct NetInfo
{
    int port;
    uint32_t ipAddrInt;
};

class ConfigReader
{

public:
    ConfigReader( const std::string& nameFile );
    uint32_t getIpBalancer() const ;
    uint16_t getPortBalancer() const ;
    size_t getCountNodes () const;
    const NetInfo& getNetInfoOfNode (size_t index ) const;
    int getLimitDatagram () const;

private:
    void initSettingBalancer (const std::map<std::string, std::string>& configFromFile );
    void initNodesConfig ( const std::map<std::string, std::string>& configFromFile );

private:
  NetInfo _networkBalancer;
  int _limitDatagramm;
  std::vector <NetInfo> _paramNodes;
};

