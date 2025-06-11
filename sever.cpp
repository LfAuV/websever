#include <iostream>
#include <unistd.h>         // close()
#include <cstring>          // memset
#include <netinet/in.h>     // sockaddr_in
#include <arpa/inet.h>      // htons, htonl
#include <ctime>            // time()

#define PORT 8888           // 我们使用高位端口，不需要 sudo
#define BACKLOG 10          // 等待连接的最大数量

int main() {
    // 1. 创建 socket
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        perror("socket creation failed");
        return 1;
    }

    // 2. 设置服务器地址
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;                // IPv4
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // 任意本地地址
    servaddr.sin_port = htons(PORT);              // 设置监听端口

    // 3. 绑定地址和端口
    if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        close(listenfd);
        return 1;
    }

    // 4. 监听
    if (listen(listenfd, BACKLOG) < 0) {
        perror("listen failed");
        close(listenfd);
        return 1;
    }

    std::cout << "服务器已启动，正在监听端口 " << PORT << " ..." << std::endl;

    while (true) {
        // 5. 接受连接
        int connfd = accept(listenfd, nullptr, nullptr);
        if (connfd < 0) {
            perror("accept failed");
            continue;
        }

        // 6. 构造欢迎消息
        time_t now = time(nullptr);
        std::string msg = "[Echo Server] Hello, client!\nCurrent time: " + std::string(ctime(&now));

        // 7. 发送消息并关闭连接
        write(connfd, msg.c_str(), msg.size());
        close(connfd);
    }

    close(listenfd);
    return 0;
}
