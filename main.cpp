#include "unp.hpp"


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

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        err_sys("socket error!");
    }

    memset(&servaddr, 0, sizeof(servaddr));// 清空
    servaddr.sin_family = AF_INET;

    // cout << "AF_INET=" << AF_INET << endl;

    servaddr.sin_port = htons(13); // 设置端口号（13 是 Daytime 服务的默认端口）

    /*
    inet_pton是一个函数，从文本到网络（无所谓）->将用户输入的IP地址字符串（如"127.0.0.1"）
    转换为网络字节序的二进制格式，并存储到 servaddr.sin_addr 中。
    Input:
    第一个参数 AF_INET 表示使用 IPv4 地址族。
    第二个参数 argv[1] 是你从命令行获取的 IP 地址字符串。
    第三个参数 &servaddr.sin_addr 是转换后存储的目标地址（以二进制形式存储）。->结构体地址

    Output:
    成功返回1
    输入IP无效返回0
    出错返回-1

    */
    if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr)<=0){
        std::stringstream ss;
        ss << "inet_pton error for" << argv[1];
        err_quit(ss.str()); // 将 IP 字符串转换为网络字节序
    }

    return 0;
}