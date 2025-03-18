#pragma once

#include "CeglePacket/CeglePacket.h"
#include <string>
#include <arpa/inet.h>

class UDPClient {
public:
    UDPClient(const std::string& serverIP, int serverPort);
    ~UDPClient();

    void sendCeglePacket(CeglePacket packet);
    
private:
    int sockfd;
    sockaddr_in servaddr;
};