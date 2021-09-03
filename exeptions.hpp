#pragma once

#include <exception>
#include <string>

class ConfigFileException : public std::exception {

public:
   explicit ConfigFileException ( const std::string& msg = "");

   virtual const char* what() const noexcept;

private:
   std::string _msg;
};

class SocketExeption : public std::exception {

public:
    explicit SocketExeption (const std::string& msg = "");
    virtual const char* what() const noexcept;

private:
   std::string _msg;
};
