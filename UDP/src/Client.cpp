// Client.cpp
#include <vector>
#include "../include/Client.hpp"

using namespace std;

/*
* This function is to get the relative path of the file in floder
* 
* @param: path, the relative path of floder
* @param: error, the instance of Error to provide (system)feedback when error occur.
* @param: res, the vector to store the relative path of the file in floder
*/
void getFileList(string path, Error error,vector<string>& res);

/*
* This function is to get the management information of the file
*
* @param: path, the realtive path and name of the file
* @param: error, the instance of Error to provide (system)feedback when error occur.
* @param: attr, the create or modify time of the file
* @param: size, the size of the file
*/
void getFileAttribution(string path, Error error, string& attr, char size[]);

Client::Client()
{
    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        error.errorMessage(SOCKET_ERROR);
    } else {
        memset(buffer,'\0',sizeof(buffer));

        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;

        struct timeval timeout={0,200000}; //0.2s  timeout
        int ret1, ret2;
        ret1 = setsockopt(socket_fd,SOL_SOCKET,SO_SNDTIMEO,&timeout,sizeof(timeout));  //sento timeout
        ret2 = setsockopt(socket_fd,SOL_SOCKET,SO_RCVTIMEO,&timeout,sizeof(timeout));  //recvfrom timeout
        if (ret1 < 0 || ret2 <0) {
            error.errorMessage(SET_TIMEOUT_OUT);
        }
        cout << "Client initialize successfully!\n";
    }
}

Client::~Client()
{
    clientClose();
}

bool Client::connect(const char* local_ip,const char* other_ip, uint16_t port, uint16_t port2)
{
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port);

    send_addr.sin_addr.s_addr = inet_addr(other_ip);
    send_addr.sin_port = htons(port2);

    if (bind(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        error.errorMessage(BIND_ERROR);
    }
}

void Client::sendFloder()
{
    string path = "./data";
    vector<string> file_name;
    string file_time;    //access_time && modify_time
    char file_size[16];
    
    getFileList(path,error,file_name);

    //Number of files
    char flag[128] = "@";
    string flag_ = to_string(file_name.size());
    strcat(flag,flag_.c_str());
    memset(buffer,'\0',sizeof(buffer));
    strcpy(buffer, flag);
    do{
        sendBuffer(1+flag_.length());
    } while (!recieveConfirm());

    for (int i = 0; i < file_name.size(); ++i) {
        getFileAttribution(file_name[i],error,file_time,file_size);
        cout<<"The N.O. "<<(i+1)<<" file is sending...\n";
        sendFileInfo(file_size, file_name[i], file_time);
        sendFile(file_name[i]);
    }
}

void Client::sendFileInfo(const char file_size[],string file_name, string file_time)
{
    cout << "The management information of " << file_name << " is transporting now.\n";    
    int len;
    //send size of file
    len = strlen(file_size);
    strcpy(buffer,file_size);
    buffer[len] = '\0';
    do{
        sendBuffer(len);
    } while (!recieveConfirm());

    //send path&name of file
    len = file_name.length();
    strcpy(buffer, file_name.c_str());
    buffer[len] = '\0';
    do{
        sendBuffer(len);
    } while (!recieveConfirm());

    //sen last access or modify time
    len = file_time.length();
    strcpy(buffer, file_time.c_str());
    buffer[len] = '\0';
    do{
        sendBuffer(len);
    } while (!recieveConfirm());    

    cout << "Over.\n";
}

void Client::sendFile(string file_name)
{
    fstream infile;
    infile.open(file_name);
    if (!infile.is_open()) {
        error.errorMessage(FILE_ERROR);
    }

    cout << "The file: " << file_name << " is transporting now.\n";    

    while (infile.peek()!= EOF) {
        infile.read(buffer,CLIENT_BUFFER_LEN);
        int len = infile.gcount();
        do{
            sendBuffer(len);
        } while (!recieveConfirm());
    }
    memset(buffer,'\0',sizeof(buffer));
    do{
        sendBuffer(0);
    } while (!recieveConfirm());

    infile.close();
    cout<<"Over.\n";
}

bool Client::recieveConfirm()
{
    char recv_buf[128];
    int len = sizeof(struct sockaddr);
    int l;
    if (0 > (l = recvfrom(socket_fd, recv_buf, sizeof(recv_buf), 0, (struct sockaddr*)&server_addr, (socklen_t *)&len))) {
        cout<<"function \"recieveConfirm\": recvfrom()<0\n";
        return false;
    } else {
        recv_buf[l] = '\0';
        return true;
    }
}

void Client::sendBuffer(int len)
{
    if(sendto(socket_fd, buffer, len, 0, (struct sockaddr*)&send_addr, sizeof(struct sockaddr)) < 0) {
        error.errorMessage(SEND_ERROR);
    } else {
        //cout << "Sending \"" << buffer <<"\"\n";
    }
}

void Client::clientClose()
{
    close(socket_fd);
}

void getFileList(string path, Error error,vector<string>& res)
{
    DIR *dir;
    struct dirent *ptr;
    char base[1024];

    if ((dir = opendir(path.c_str())) == NULL) {
        error.errorMessage(DIR_ERROR);
    }
    cout<<"File path colletcing...\n";
    while ((ptr = readdir(dir)) != NULL) {
        if (strcmp(ptr->d_name,".") == 0 || strcmp(ptr->d_name, "..") == 0) {
            continue;
        } else if (ptr->d_type == 8) {  //file
            cout<<string(path)+"/"+string(ptr->d_name)<<endl;
            res.push_back(string(path)+"/"+string(ptr->d_name));
        } else if (ptr->d_type == 10) { //link file
            cout<<string(path)+"/"+string(ptr->d_name)<<endl;
            res.push_back(string(path)+"/"+string(ptr->d_name)); 
        } else if (ptr->d_type == 4) {  //dir
             memset(base,'\0',sizeof(base)); 
             strcpy(base,path.c_str()); 
             strcat(base,"/"); 
             strcat(base,ptr->d_name); 
             getFileList(base,error,res);
        }
    }

    closedir(dir);
}

void getFileAttribution(string path, Error error, string& attr, char size[])
{
    struct stat b;
    if (stat(path.c_str(),&b) == -1) {
        error.errorMessage(FILE_ERROR);
    }

    time_t hold = b.st_atim.tv_sec;
    struct tm* times;
    time(&hold);
    times = localtime(&hold);
    attr = to_string(times->tm_year + 1900);
    attr += (times->tm_mon+1) < 10? ("0"+to_string(times->tm_mon+1)) : to_string(times->tm_mon+1);
    attr += (times->tm_mday < 10) ? ("0" + to_string(times->tm_mday)) : to_string(times->tm_mday);
    attr += (times->tm_hour < 10) ? ("0" + to_string(times->tm_hour)) : to_string(times->tm_hour);
    attr += (times->tm_min < 10) ? ("0" + to_string(times->tm_min)) : to_string(times->tm_min);

    strcpy(size,to_string(b.st_size).c_str());
}

