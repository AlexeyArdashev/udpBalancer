#include "balancer.hpp"

#include <iostream>

namespace {
const char* NAME_FILE_CONFIG = "config.txt";
}

Balancer::Balancer() :
    _config( new ConfigReader(NAME_FILE_CONFIG) ),
    _socket( new UdpSocket (_config->getIpBalancer(), _config->getPortBalancer()) ),
    _limiter( new Limiter ( _config->getLimitDatagram() ) )
{
}

void Balancer::start()
{
    std::array <char, UdpSocket::SIZE_BUFFER> buffer;
    size_t currentIndexNode = 0;
    size_t countNodes = _config->getCountNodes();
    while (1) {

       int readed_bytes = _socket->startWaitingDatagrams( buffer );
       auto first = buffer.begin();
       auto last = first + readed_bytes;
     //  std::string msg (first, last);
       std::vector<char>  data (first, last );
     //  std::cout << "come datagram with size " << data.size() << std::endl;
     //  std::cout << msg << std::endl;
       if ( !_limiter ->isExceedingLimit() ) {
        //   std::cout<< "msg was ignored\n";
           continue;
       }
       _socket->sendData( _config->getNetInfoOfNode(currentIndexNode).ipAddrInt,
                          _config->getNetInfoOfNode(currentIndexNode).port,
                          data );
       ++currentIndexNode;
       _limiter->msgWasSend();
       if ( currentIndexNode >= countNodes )
           currentIndexNode = 0;
    }
}
