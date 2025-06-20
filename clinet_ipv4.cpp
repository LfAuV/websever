#include "unp.hpp"


/*

argc：命令行参数数量
argv：字符串数组，保存每个命令行参数


argv[0]->程序本身的名字
argv[1]->用户输入的参数

*/
int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "usage: " << argv[0] << " <IPaddress>" << std::endl;
        return EXIT_FAILURE;
    }

    int sockfd = ::socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        throw std::runtime_error("socket error!");
    }
    /*
    struct sockaddr_in {
    sa_family_t    sin_family;   // 地址族（Address Family），AF_INET 表示 IPv4
    in_port_t      sin_port;     // 端口号（使用 htons() 转为网络字节序）
    struct in_addr sin_addr;     // IP地址结构体（使用 inet_pton 设置）
    char           sin_zero[8];  // 填充字节（保持结构体大小与 sockaddr 一致）
    */
    sockaddr_in servaddr{};
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8888); // Daytime 服务端口
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
    if (::inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
        std::stringstream ss;
        ss << "inet_pton error for " << argv[1];
        throw std::runtime_error(ss.str());
    }

    if (::connect(sockfd, reinterpret_cast<sockaddr*>(&servaddr), sizeof(servaddr)) < 0) {
        throw std::runtime_error("connect error!");
    }

    char recvline[MAXLINE + 1];
    ssize_t n;
    while ((n = ::read(sockfd, recvline, MAXLINE)) > 0) {
        recvline[n] = '\0';
        std::cout << recvline;
    }

    if (n < 0) {
        throw std::runtime_error("read error");
    }

    ::close(sockfd);
    return 0;
}