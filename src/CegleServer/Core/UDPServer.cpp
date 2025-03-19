#include "UDPServer.h"
#include "CeglePacket.h"

#include <unistd.h>
#include <stdint.h>
#include <array>

UDPServer::UDPServer(int port) {
    /* Init UDP Server */
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(port);

    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
}

UDPServer::~UDPServer() {
    close(sockfd);
}

void UDPServer::serveForever() {
    std::array<uint8_t, MAX_PACKET_SIZE> buffer;
    socklen_t len = sizeof(cliaddr);

    while (true) {
        int n = recvfrom(sockfd, buffer.data(), sizeof(buffer), MSG_WAITALL, 
                         (struct sockaddr *)&cliaddr, &len);
        
        if (n < 2) {
            std::cout << "Received invalid packet\n";
            continue;
        }
        
        /* conver CeglePacket into SBUS/SMTH */
        sbus.mapKeyToChannel(buffer[1]);
        std::vector<uint16_t> channels = sbus.getChannels();
        std::string response = "Key received: ";
        response += buffer[1];

        response += " | Mapped Channels: ";

        for (size_t i = 0; i < channels.size(); i++) {
            response += "ch" + std::to_string(i) + ":" + std::to_string(channels[i]) + " ";
        }

        sendto(sockfd, response.c_str(), response.length(), MSG_CONFIRM, 
               (const struct sockaddr *)&cliaddr, len);

        /* Prepare SBUS Packet for UART transmitting to FC (Flight Controller) */
        std::array<uint8_t, SBUS_SIZE> packet = sbus.unpack();

        /* Sending data to STM32F4xxx FC with SBUS RX set on */
        if (!packet.empty()) {
            uart.writeData(packet.data(), packet.size());
        }
    }
}