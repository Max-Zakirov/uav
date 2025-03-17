#ifndef UDP_CLIENT_H
#define UDP_CLIENT_H

#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include "CRSF.h"

class UDPClient {
public:
    UDPClient(const std::string& serverIP, int port);
    ~UDPClient();

    void sendKey(char key);
    char getKeypress();

private:
    int sockfd;
    struct sockaddr_in servaddr;
    CRSF crsf;
};

#endif // UDP_CLIENT_H
