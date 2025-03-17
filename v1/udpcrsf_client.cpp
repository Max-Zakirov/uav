#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <termios.h>
#include "crsf_mapping.h"

#define SERVER_IP "127.0.0.1"
#define PORT 8080

char getKeyPress() {
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

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        return -1;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &servaddr.sin_addr);

    std::cout << "Press 'W', 'A', 'S', or 'D' to control, 'Q' to quit.\n";

    CRSFPacket packet;

    while (true) {
        char key = getKeyPress();
        if (key == 'q' || key == 'Q') break;

        mapKeyToCRSF(key, packet);
        addCRCToPacket(packet); // Compute CRC before sending

        sendto(sockfd, &packet, sizeof(packet), MSG_CONFIRM, (const struct sockaddr*)&servaddr, sizeof(servaddr));
        std::cout << "Sent: " << key << " (CRSF Data, CRC: " << std::hex << (int)packet.crc << ")\n";

        packet.channels[0] = 992;
        packet.channels[1] = 992;
    }

    close(sockfd);
    return 0;
}
