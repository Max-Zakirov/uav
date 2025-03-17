#ifndef UDP_SERVER_H
#define UDP_SERVER_H

#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include "CRSF.h"

class UDPServer {
public:
    UDPServer(int port);
    ~UDPServer();

    void start();

private:
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    CRSF crsf;
};

#endif // UDP_SERVER_H
