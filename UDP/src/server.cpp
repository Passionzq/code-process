#include"server_fun.h"
#include"common.h"

using std::ios;

char buffer[DEFAULT_BUFFER_SIZE + 20];

int main(){
    int client_fd, server_fd;
    struct sockaddr_in cle_addr, ser_addr;
    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        errPrint("create socket failed\n");
    printf("[main] socket initialize success!\n");
    //std::string ser_ip = "192.168.199.155"; /* change this to your ip and port */
    readyJob(client_fd, server_fd, cle_addr, ser_addr);/* readyJob(client_fd, server_fd, cle_addr, ser_addr, (string)ip, (int)port)*/
    std::string file_path = "cp_happy.ply";
    std::ofstream mfile(file_path.c_str(), ios::out);
    if(!mfile.is_open())
        errPrint("file open error\n");
    int count = 0, len = 0;
    int64_t total_count = 0, beg_time = getNowTime(), end_time;
    while(true){
        len = recv(client_fd, buffer, DEFAULT_BUFFER_SIZE, 0);
        total_count += len;
        mfile.write(buffer, len);
        if(len)
            printf("[main] receive count: %d    size: %d\n", ++count, len);
        else
            break;
    }
    end_time = getNowTime();
    std::pair<std::string, double> msg = getUnit((double)total_count);
    printf("[main] total size: %.2lf %s = %ld Bytes\n", msg.second, msg.first.c_str(), total_count);
#ifdef PRINT_TIME
    printf("[main] time: %ld ms\n", end_time - beg_time);
#endif
    msg = getUnit((double)total_count / (end_time - beg_time) * 1000);
    printf("[main] speed: %.2lf %s/s\n", msg.second, msg.first.c_str());
    mfile.close();
    close(client_fd);
    return 0;
}