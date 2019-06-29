//Client_test.cpp
#include"../include/Client.hpp"

const char local_ip[16] = "192.168.43.111";    // the ipv4 address of client
const char other_ip[16] = "192.168.43.197";    // the ipv4 address of server
int main()
{
    Client client;
    client.connect(local_ip, other_ip);
    client.sendFloder();
}