#include "UDPServer.h"
#include "Serial.h"
#include "CRSF.h"
#include <thread>
#include <chrono>

/* TODO: Make try : catch + exceptions inside the code, instead of returns of ints and bools */
int main() {
    UDPServer server(8070);

    server.serveForever();
    // CRSF crsf{};
    Serial uart("/dev/ttyUSB0");
    // auto packet = crsf.pack();

    // while (true) {
    //     for (auto i : packet) {
    //         std::cout << std::hex << int(i) << " ";
    //     }
    //     std::cout << std::endl;
        
    //     /* Sending data to STM32F4xxx FC with SBUS RX set on */
    //     if (!packet.empty()) {
    //         uart.writeData(packet.data(), packet.size());
    //     }
    //     std::this_thread::sleep_for(std::chrono::milliseconds(200));
    // }

    return 0;
}