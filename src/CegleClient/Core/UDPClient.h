#ifndef UDP_CLIENT_H
#define UDP_CLIENT_H

#include <arpa/inet.h>
#include "CeglePacket/CeglePacket.h"

class UDPClient {
public:
    UDPClient(const std::string& serverIP, int serverPort);
    ~UDPClient();

    void sendCeglePacket(CeglePacket packet);
    
private:
    int sockfd;
    sockaddr_in servaddr;
};

#endif // UDP_CLIENT_H
