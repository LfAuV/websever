#ifndef __unp_h
#define __unp_h

#include<iostream>
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>      // memset
#include <cstdlib>      // exit
#include <unistd.h>     // read, close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // sockaddr_in
#include <arpa/inet.h>  // inet_pton
#include <errno.h>

#define MAXLINE 4096

void err_quit(const std::string& msg){
    std::cerr<< msg << std::endl;
    exit(EXIT_FAILURE);
}

void err_sys(const std::string& msg){
    perror(msg.c_str());
    exit(EXIT_FAILURE);
}



#endif