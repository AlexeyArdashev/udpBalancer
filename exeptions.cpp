#include "exeptions.hpp"

ConfigFileException::ConfigFileException(  const std::string& msg )
{
    _msg += "Error config file: ";
    _msg += msg;
}

const char *ConfigFileException::what() const noexcept
{
   return _msg.data();
}

SocketExeption::SocketExeption(const std::string &msg)
{
    _msg += "Error socket: ";
    _msg += msg;
}

const char *SocketExeption::what() const noexcept
{
      return _msg.data();
}

