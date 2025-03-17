#include "UDPClient.h"
#include <iostream>

int main() {
    UDPClient client("127.0.0.1", 8080); // Replace with actual RPi IP

    std::cout << "Press W/A/S/D to send commands. Press 'q' to quit.\n";

    while (true) {
        char key = client.getKeypress();
        if (key == 'q') break; // Exit loop on 'q'
        client.sendKey(key);
    }

    return 0;
}
