// Error.cpp
#include "../include/Error.hpp"

Error::Error()
{
    ;
}

Error::~Error()
{
    ;
}

void Error::errorMessage(ERROR_TYPE error_num)
{
    switch(error_num){
      case SOCKET_ERROR:
        perror("Socket ");
        exit(-1);
        break;
    
      case BIND_ERROR:
        perror("Bind ");
        exit(-1);
        break;

      case SEND_ERROR:
        perror("Send ");
        break;

      case DIR_ERROR:
        perror("Directory ");
        break;
      
      case FILE_ERROR:
        perror("File ");
        break;

      case SET_TIMEOUT_OUT:
        perror("Set time out ");
        break;

      default:
        break;
    }
}