#include "udpsocket.hpp"
#include "exeptions.hpp"

#include <iostream>
#include <netinet/in.h>

void ipIntDecomposeToByte(unsigned int ip, std::array <uint8_t, 4>& bytes )
{
    bytes[0] = ip & 0xFF;
    bytes[1] = (ip >> 8) & 0xFF;
    bytes[2] = (ip >> 16) & 0xFF;
    bytes[3] = (ip >> 24) & 0xFF;
}

UdpSocket::UdpSocket( uint32_t ip, uint16_t port ) :
    _descrSocket (-1)
{
    sockaddr_in paramSocket;
    paramSocket.sin_family = AF_INET;
    paramSocket.sin_port = htons( port );
    paramSocket.sin_addr.s_addr = htonl( ip );
    _descrSocket = socket(AF_INET, SOCK_DGRAM, 0);

    if(_descrSocket < 0 )
    {
        std::cout << "socket\n";
        exit(1);
    }
    if( bind( _descrSocket, (struct sockaddr *)&paramSocket, sizeof(paramSocket) ) < 0 )
    {
        std::string msg = "socket not bind to ";
        std::array <uint8_t, 4> bytes;
        ipIntDecomposeToByte (ip, bytes);
        for ( size_t i = bytes.size(); i > 0 ; i--)
        {
            msg += std::to_string(bytes[i - 1 ]);
            if (i != 1) msg += ".";
        }
        msg += " port: ";
        msg += std::to_string(port);
        throw SocketExeption (msg);
    }
}

void UdpSocket::sendData( uint32_t ip, uint16_t port, const std::vector<char> &data ) const
{
    struct sockaddr_in receiver;
    receiver.sin_family = AF_INET;
    receiver.sin_port = htons(port);
    receiver.sin_addr.s_addr = htonl(ip);

    sendto(_descrSocket, data.data(),data.size(), 0,
           (struct sockaddr *)&receiver, sizeof(receiver));
}

int UdpSocket::startWaitingDatagrams(std::array<char, SIZE_BUFFER> &buf ) const
{
    int bytes_read = recvfrom(_descrSocket, buf.data(), buf.size(), 0, NULL, NULL);
    return bytes_read;
}
