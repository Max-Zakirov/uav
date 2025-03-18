#include "CegleApp.h"
#include "CeglePacket.h"

void CegleApp::run() {
    std::cout << "Press W/A/S/D to send commands. Press 'q' to quit.\n";

    while (true) {
        char key = keyboardManager.getKeypress();
        if (key == 'q') break;
        CeglePacket packet{PROTOCOL_TYPE_CRSF, key};
        packet.key = key;
        client.sendCeglePacket(packet);
    }
}