#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "crsf_mapping.h"

#define PORT 8080

int main() {
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    CRSFPacket packet;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        return -1;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    if (bind(sockfd, (const struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("Bind failed");
        return -1;
    }

    std::cout << "CRSF UDP Server listening on port " << PORT << "...\n";

    while (true) {
        socklen_t len = sizeof(cliaddr);
        int n = recvfrom(sockfd, &packet, sizeof(packet), MSG_WAITALL, (struct sockaddr*)&cliaddr, &len);

        if (n > 0) {
            uint8_t data[9];
            memcpy(data, &packet, 8);
            uint8_t computed_crc = calculateCRC8(data, 8);

            if (computed_crc != packet.crc) {
                std::cout << "Invalid CRC! Received: " << std::hex << (int)packet.crc
                          << ", Expected: " << (int)computed_crc << "\n";
                continue;
            }

            std::cout << "Received CRSF Data (Valid CRC)\n";
            std::cout << "Throttle (Ch1): " << packet.channels[0] << "\n";
            std::cout << "Roll (Ch2): " << packet.channels[1] << "\n";
            std::cout << "Pitch (Ch3): " << packet.channels[2] << "\n";
            std::cout << "Yaw (Ch4): " << packet.channels[3] << "\n";
        }
    }

    close(sockfd);
    return 0;
}
