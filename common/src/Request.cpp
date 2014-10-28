#include "Request.hpp"

Request::Request(PacketType type)
: APacket(type)
{
    
}

Request::~Request()
{
    
}

#include <iostream>

void Request::print()
{
    std::cout << (int)_type << std::endl;
}

std::vector<char> Request::to_bytes_body() const
{
    return (std::vector<char>());
}

std::string Request::to_readable_body() const
{
    return ("");
}

void Request::from_bytes_body(const std::vector<char> &)
{
    
}

void Request::from_readable_body(const std::string &)
{
    
}
