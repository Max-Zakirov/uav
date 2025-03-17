#include "UDPClient.h"
#include <unistd.h>
#include <termios.h>

UDPClient::UDPClient(const std::string& serverIP, int port) {
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    inet_pton(AF_INET, serverIP.c_str(), &servaddr.sin_addr);
}

UDPClient::~UDPClient() {
    close(sockfd);
}

void UDPClient::sendKey(char key) {
    std::vector<uint8_t> data = {static_cast<uint8_t>(key)};
    uint8_t crc = crsf.calculateCRC8(data);
    data.push_back(crc);

    sendto(sockfd, data.data(), data.size(), MSG_CONFIRM, 
           (const struct sockaddr *)&servaddr, sizeof(servaddr));

    char buffer[1024];
    socklen_t len;
    int n = recvfrom(sockfd, buffer, sizeof(buffer), MSG_WAITALL, 
                     (struct sockaddr *)&servaddr, &len);
    buffer[n] = '\0';
    std::cout << "Server: " << buffer << std::endl;
}

// ✅ Capture keypresses without pressing Enter
char UDPClient::getKeypress() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
