/*
* Client.hpp
*
* Author: Qi Zhang
* Date: 2019-05-17
* The purpose of this head file is to provide the class Clinet 
* and the declations of its method. 
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <cstring>
#include <ctime>
#include <unistd.h>
#include <dirent.h>
#include <fstream>
#include <chrono>
#include <iostream>
#include <string>
#include "../include/Error.hpp"

#define CLIENT_BUFFER_LEN 40000
#define DEFAULT_CLIENT_PORT 8011
#define DEFAULT_OTHER_PORT 8026

using namespace std::chrono;

class Client {
  public:
    /*
    * Constructor of Clinet.
    * Initilize the socket_fd, buffer, server_addr
    * Set the timeout of recvfrom().
    */
    Client();

    /*
    * Destructor of Client.
    * Close the socket
    */
    ~Client();

    /*
    * This method is to set and bind the ip address.
    * 
    * @param: local_ip, the ipv4 address of client(local)
    * @param: ip, the ipv4 address of server
    * @param: port, the port of client to send or recieve
    * @param: port2, the port of server to send or recieve
    * 
    * return value: whether the ip address has binded with the port 
    */
    bool connect(const char* local_ip,const char* ip, 
                uint16_t port = DEFAULT_CLIENT_PORT, uint16_t port2 = DEFAULT_OTHER_PORT);
    
    /*
    * This method is to send all the files in floder "../data/"
    */
    void sendFloder();

    /*
    * This method is to send the managment infomation of file.
    * 
    * @param: file_size[], size (in bytes) of the file
    * @param: file_name, the relative path and name of the file
    * @param: file_time, the create time and modify time of the file
    */
    void sendFileInfo(const char file_size[],std::string file_name,std::string file_time);
    
    /*
    * This method is to send the content of the file
    * 
    * @param: file_name, the relative path and name of the file
    */
    void sendFile(std::string file_name);

    /*
    * This file is to recieve the confirm from server to ensure 
    * that server had recieved the content.
    * 
    * return value: whether the server has recieved the content  
    */
    bool recieveConfirm();

    /*
    * This value is to send the buffer of length to server
    * 
    * @param: len, the length of buffer to send
    */
    void sendBuffer(int len);

    /*
    * This method to close socket.
    */
    void clientClose();
    
  private:
    int socket_fd;  //socket descriptor
    struct sockaddr_in server_addr; //the info of local network
    struct sockaddr_in send_addr;   //the info of server's network
    char buffer[CLIENT_BUFFER_LEN]; 
    Error error;    //error handling
};

#endif