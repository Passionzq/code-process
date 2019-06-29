/*
* Error.hpp
*
* Author: Qi Zhang
* Date: 2019-05-17
* The purpose of this head file is to provide (system)feedback 
* on errors that may occur during the execution of Client and Server. 
*/
#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <cstdio>
#include <cstdlib>

#define SOCKET_ERROR 1
#define BIND_ERROR 2
#define SEND_ERROR 3
#define DIR_ERROR 4
#define FILE_ERROR 5
#define SET_TIMEOUT_OUT 6

typedef int ERROR_TYPE;

class Error{
  public:
    Error();
    ~Error();

    //@param: error_num, the error_type defined above.
    void errorMessage(ERROR_TYPE error_num);
};

#endif