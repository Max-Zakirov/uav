#include "UDPServer.h"
#include "CeglePacket/CeglePacket.h"

#include <unistd.h>
#include <stdint.h>
#include <array>

UDPServer::UDPServer(int port) {
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

// const string UART_PORT = "/dev/ttyAMA0";
// const uint32_t UART_BAUDRATE = 115200;

// serial::Serial uart(UART_PORT, UART_BAUDRATE, serial::Timeout::simpleTimeout(1000));

// while (1) {
//   CRSF *buffer = socket.receive_from();

//   if (buffer) {
//     uart.write(crsf_packet);
//     std::cout << "CRSF sent via UART, size: " << crsf_packet.size() << " bytes." << std::endl;
//   }
//   std::this_thread::sleep_for(std::chrono::milliseconds(10));
// }

UDPServer::~UDPServer() {
    close(sockfd);
}
void UDPServer::run() {
    std::array<uint8_t, MAX_PACKET_SIZE> buffer;
    socklen_t len = sizeof(cliaddr);

    while (true) {
        int n = recvfrom(sockfd, buffer.data(), sizeof(buffer), MSG_WAITALL, 
                         (struct sockaddr *)&cliaddr, &len);
        
        if (n < 2) { // Ignore invalid packets
            std::cout << "Received invalid packet\n";
            continue;
        }
        
        /* conver CeglePacket into CRSF/SMTH */
        crsf.mapKeyToChannel(buffer[1]);
        std::vector<uint16_t> channels = crsf.getChannels();

        std::array<uint8_t, CRSF_SIZE> packet = crsf.unpack();

        /* UART.send() */

        // Print CRSF Channel Values
        std::cout << "Mapped Channels: ";
        for (size_t i = 0; i < channels.size(); i++) {
            std::cout << "Ch" << i << ":" << channels[i] << " ";
        }
        std::cout << std::endl;

        // Send response back
        std::string response = "Key received: ";
        response += buffer[0];

        sendto(sockfd, response.c_str(), response.length(), MSG_CONFIRM, 
               (const struct sockaddr *)&cliaddr, len);
    }
}