// Server.cpp
#include "../include/Server.hpp"

const char* local_ip = "192.168.199.155";   //The ipv4 address of server
const char* other_ip = "192.168.199.155";   //The ipv4 address of client

int main()
{
    Server server;
    server.connect(local_ip, other_ip);
    server.reciveFloder();
}   