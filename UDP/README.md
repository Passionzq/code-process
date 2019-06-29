## Function
Transport orderly all the file in specific floder without losing packetages by UDP.   

## How to run
```
cd UDP
make
<terminal 1> ./bulid/server
<terminal 2> ./bulid/client
```
## Transport files
You can put the file you want to transport into the floder "data", and the project will send it all to the server.   

## Version
- 0.0.1: 完成传输不丢包且有序的传输。

## Attention
- 本程序需要在Linux环境下运行，在运行前，需要更改Client 和 Server对应的ip地址，具体操作如下：   

*./src/Client_test.cpp* 
```
const char local_ip[16] = "192.168.199.155";    //更改为Client的ipv4地址
const char other_ip[16] = "192.168.199.221";    //更改为Server的ipv4地址
``` 
*./src/Server_test.cpp*
```
const char local_ip[16] = "192.168.199.155";    //更改为Server的ipv4地址
const char other_ip[16] = "192.168.199.221";    //更改为Client的ipv4地址
``` 

- 本程序只能发送文件，不能在Server端创建相应的文件夹（路径），如果需要发送的内容中有文件夹，那么需要事先在Server端的data文件夹下创建相同的文件夹。

- 请在**UDP文件夹下**运行以下指令
```
<terminal 1> ./bulid/server
<terminal 2> ./bulid/client
```
而不要进入bulid文件夹下运行，因为程序中使用的是以UDP文件夹为基础的**相对路径**。

- 请在运行程序前将Server端的data文件夹下的文件删除（只删文件不要删除文件夹）

- 如果端口被占用，可以修改 *Client.hpp* 和 *Server.hpp* 中宏定义中的 *#define DEFAULT_xx_PORT* 请注意两个文件的”一致性“。
