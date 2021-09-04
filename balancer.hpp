#pragma once

#include "configreader.hpp"
#include "udpsocket.hpp"
#include "limiter.hpp"

#include <memory>

class Balancer
{
public:
    explicit Balancer( const std::string& fileName );
    void start();

private:
    std::unique_ptr<ConfigReader> _config;
    std::unique_ptr<UdpSocket> _socket;
    std::unique_ptr<Limiter> _limiter;
    size_t countNodes;
};

