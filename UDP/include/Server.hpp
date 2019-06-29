/*
* Server.hpp
*
* Author: Qi Zhang
* Date: 2019-05-17
* The purpose of this head file is to provide the class Server 
* and the declations of its method. 
*/
#ifndef SERVER_HPP_
#define SERVER_HPP_

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
#include "../include/Error.hpp"

#define DEFAULT_SERVER_PORT 8026
#define DEFAULT_OTHER_PORT 8011
#define SERVER_BUFFER_LEN 40000
#define BASE 1024
#define MILLION_DENO 1000000

class Server{
  public:
    /*
    * Constructor of Server
    * Initilize the socket_fd, buffer, buffer_cmp, server_addr
    * Set the timeout of recvfrom().
    */
    Server();

    /*
    * Destructor of Server.
    * Close the socket
    */
    ~Server();

    /*
    * This method is to set and bind the ip address.
    * 
    * @param: local_ip, the ipv4 address of server(local)
    * @param: ip, the ipv4 address of client
    * @param: port, the port of server to send or recieve
    * @param: port2, the port of client to send or recieve
    * 
    * return value: whether the ip address has binded with the port 
    */
    bool connect(const char* local_ip,const char* other_ip, uint16_t port = DEFAULT_SERVER_PORT, uint16_t port2 =DEFAULT_OTHER_PORT);
    
    /*
    * This method is to recieve the buffer of specific length abd 
    * 
    * @param: length, the length of buffer want to get
    * 
    * return value: whether the content of specific length has recieved
    */
    bool reciveBuffer(int& length);

    /*
    * This method is to recieve the management info of the file
    * that will recieve and use them to ctreate the file in same path.
    * 
    * @param: file_size, the size (in bytes) that the file that would recieve
    * @param: file_name, the realative path and the name of the file that would recieve
    * @paran: file_time, the create and modify time of the file that would recieve
    */
    void reciveFileInfo(char file_size[], std::string &file_name, std::string& file_time);
    
    /*
    * This method is to recieve the content of the file in specific realative path
    * 
    * @param: file_size, the size of the file
    * @path: the relative path of the file to write content in.
    */
    void reciveFile(int fize_size, std::string& path);
    
    /*
    * This method is to recieve the all files and store in the specific floder
    * (need to build the same path as client, or it will occor floder error)
    */
    void reciveFloder();

    /*
    * This method is to close the socket.
    */
    void serverClose();
    
  private:
    int socket_fd;  //socket descriptor
    struct sockaddr_in server_addr; //the info of local network
    struct sockaddr_in send_addr;   //the info of client network
    char buffer[SERVER_BUFFER_LEN]; 
    char buffer_cmp[SERVER_BUFFER_LEN]; //the buffer to compare the if the content recieve is same as before
    int64_t start, end; //timer
    Error error; //error handling
};
#endif
