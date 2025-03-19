#ifndef UDP_SERVER_H
#define UDP_SERVER_H

#include "SBUS.h"
#include "Serial.h"

#include <iostream>
#include <cstring>
#include <arpa/inet.h>

constexpr char UART_PORT[] = "/dev/ttyAMA0";

class UDPServer {
public:
    UDPServer() = delete;
    UDPServer(int port);
    ~UDPServer();

    void serveForever();

private:
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    SBUS sbus{};
    Serial uart{UART_PORT};
};

#endif // UDP_SERVER_H
