//Server.cpp
#include "../include/Server.hpp"

using namespace std;

/*
* This function is to get the time point,
* so that we can calculate the transport time.
*/
int64_t getNowTime();

/*
* This function is to transfrom the Unit of the speed(Byte/s to MB/s)
*/
std::pair<std::string, double> getUnit(double num);

Server::Server()
{
    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        error.errorMessage(SOCKET_ERROR);
    } else {      
        memset(buffer,'\0', sizeof(buffer));
        memset(buffer_cmp,'\0', sizeof(buffer_cmp));

        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

        struct timeval timeout={1,0}; //1s  timeout
        int ret1, ret2;
        ret1 = setsockopt(socket_fd,SOL_SOCKET,SO_SNDTIMEO,&timeout,sizeof(timeout));  //sento timeout
        int on=1;
        ret2 = setsockopt(socket_fd,SOL_SOCKET,SO_REUSEADDR | SO_BROADCAST,&on,sizeof(on));
        if (ret1 < 0 || ret2 <0) {
            error.errorMessage(SET_TIMEOUT_OUT);
        }

        cout << "Server initialize successfully.\n";
    }
}

Server::~Server()
{
    serverClose();
}

bool Server::connect(const char* local_ip, const char* other_ip, uint16_t port, uint16_t port2)
{
    server_addr.sin_addr.s_addr = inet_addr(local_ip);
    server_addr.sin_port = htons(port);

    send_addr.sin_addr.s_addr = inet_addr(other_ip);
    send_addr.sin_port = htons(port2);
    
    if (bind(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        error.errorMessage(BIND_ERROR);
    }
}

bool Server::reciveBuffer(int& length)
{   
    memset(buffer,'\0',sizeof(buffer));
    int len = sizeof(struct sockaddr);
    if (0 > (length = recvfrom(socket_fd, buffer, SERVER_BUFFER_LEN, 0,(struct sockaddr*)&server_addr, (socklen_t *)&len))) {
        return false;
    } else {
        if (sendto(socket_fd, "Get", 4, 0, (struct sockaddr*)&send_addr, sizeof(struct sockaddr)) < 0) {
            error.errorMessage(SEND_ERROR);
            return false;
        } else {
            //cout << "Recive "<<buffer<<endl;
            return true;
        }
    }
}

void Server::reciveFileInfo(char file_size[],string& file_name, string& file_time)
{
    int l;
    //size
    do{ 
        reciveBuffer(l);
        buffer[l] = '\0'; 
        strcpy(file_size, buffer);
    }while(strcmp(buffer, buffer_cmp) == 0);
    strcpy(buffer_cmp, buffer);
    buffer_cmp[l] = '\0';

    //path
    do{
        reciveBuffer(l);
        buffer[l] = '\0'; 
        file_name = buffer;
    }while(strcmp(buffer, buffer_cmp) == 0);
    strcpy(buffer_cmp, buffer);
    buffer_cmp[l] = '\0';


    //time
    do{
        reciveBuffer(l);
        buffer[l] = '\0';
        file_time = buffer;
    }while(strcmp(buffer, buffer_cmp) == 0);
    strcpy(buffer_cmp, buffer);
    buffer_cmp[l] = '\0';

    //create the file
    string order = "touch " + file_name +" -t "+ file_time; 
    cout<<"Terminal order: "<<order<<endl;
    system(order.c_str());    
}

void Server::reciveFile(int file_size, string& path)
{
   fstream fp;
   fp.open(path.c_str(),ios::out);
   if (!fp.is_open()) {
       error.errorMessage(FILE_ERROR);
   } else {
       cout<<"File "<< path <<" is open now\n";
   }
   int counter = 0;
   int x;
   do{
       reciveBuffer(x);
       fp.write(buffer,x);
       counter += x;
       cout << "size: " << x <<endl;
   }while(x != 0);
   fp.close();
   cout<<"File "<<path <<"is close now.\t File size: "<<counter<<endl;
}

void Server::reciveFloder()
{
    char char_file_size[128];
    string file_path;
    string file_time;
    int file_size;

    do{
        int x;
        reciveBuffer(x);
    }while(strncmp(buffer, "@", 1) != 0);
    this->start = getNowTime();
    strcpy(buffer_cmp, buffer);

    int file_nums;
    char char_file_nums[128];
    for(int i = 1; i<strlen(buffer); ++i) {
        char_file_nums[i-1] = buffer[i];
    }
    char_file_nums[strlen(buffer)-1] = '\0';
    file_nums = atoi(char_file_nums);
    cout<<"Server will recieve "<<file_nums<<" files.\n";

    long long total_size = 0;

    for(int i = 0; i<file_nums; ++i) {
        cout<<"This is the N.O. "<<(i + 1)<<" file.\n";
        reciveFileInfo(char_file_size, file_path, file_time);
        file_size = atoi(char_file_size);
        total_size += file_size;
        reciveFile(file_size, file_path);
    }

    this->end = getNowTime();
    std::pair<std::string, double> msg = getUnit((double)total_size * 1000 / (end -start));
    cout<<"Time: "<<end-start<<" ms\tTotal size: "<< total_size<<endl;
    cout << "Speed: " << msg.second << " " << msg.first << "/s" << endl;
}

void Server::serverClose()
{
    close(socket_fd);
}

int64_t getNowTime()
{
    return std::chrono::system_clock::now().time_since_epoch().count() / MILLION_DENO;
}

std::pair<std::string, double> getUnit(double num)
{
    int count = 0;
    while(num > BASE){
        num /= BASE;
        if(++count >= 3)
            break;
    }
    std::string str;
    if(!count)
        str = "B";
    else if(count == 1)
        str = "KB";
    else if(count == 2)
        str = "MB";
    else if(count >= 3)
        str = "GB";
    return std::make_pair(str, num);
}