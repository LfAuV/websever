#include "unp.hpp"
using namespace std;

/*

argc：命令行参数数量
argv：字符串数组，保存每个命令行参数


argv[0]->程序本身的名字
argv[1]->用户输入的参数

*/
int main(int argc, char**argv){

    int sockfd, n;

    char recvline[MAXLINE + 1];
    /*
    struct sockaddr_in {
    sa_family_t    sin_family;   // 地址族（Address Family），AF_INET 表示 IPv4
    in_port_t      sin_port;     // 端口号（使用 htons() 转为网络字节序）
    struct in_addr sin_addr;     // IP地址结构体（使用 inet_pton 设置）
    char           sin_zero[8];  // 填充字节（保持结构体大小与 sockaddr 一致）
};*/
    struct sockaddr_in servaddr;
    
    if(argc != 2){
        err_quit("usage: a.out <IPaddress>");
    }
    return 0;
}