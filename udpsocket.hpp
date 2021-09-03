#pragma once

#include <stdint.h>
#include <array>
#include <vector>
#include <memory>
#include <netinet/in.h>

class UdpSocket
{

public:
    static const int SIZE_BUFFER = 1024;
    UdpSocket( uint32_t ip, uint16_t port );
    int startWaitingDatagrams ( std::array <char, SIZE_BUFFER>& buf ) const ;
    void sendData ( uint32_t ip, uint16_t port, const std::vector <char>& data ) const ;

private:
    int _descrSocket;
    std::unique_ptr<sockaddr_in> _paramSocket;
};
