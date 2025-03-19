#include "CegleApp.h"
#include "CeglePacket.h"

#include <iostream>

CegleApp::CegleApp(const std::string& serverIP, int serverPort) : client {serverIP, serverPort}{}

void CegleApp::run() {
    std::cout << "Press W/A/S/D to send commands. Press 'p' to quit.\n";

    while (true) {
        char key = keyboardManager.getKeypress();
        if (key == 'p') break;
        CeglePacket packet{PROTOCOL_TYPE_SBUS, key};
        packet.key = key;
        client.sendCeglePacket(packet);
    }
}