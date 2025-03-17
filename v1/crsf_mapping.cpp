#include "crsf_mapping.h"
#include <cstring> // For memcpy

void mapKeyToCRSF(char key, CRSFPacket &packet) {
    switch (key) {
        case 'w': packet.channels[0] = 1092; break; // Throttle Up
        case 's': packet.channels[0] = 892; break;  // Throttle Down
        case 'a': packet.channels[1] = 892; break;  // Roll Left
        case 'd': packet.channels[1] = 1092; break; // Roll Right
        default: return;
    }
}

// Compute CRC and update packet before sending
void addCRCToPacket(CRSFPacket &packet) {
    uint8_t data[9]; // Header + Length + Type + Channels
    memcpy(data, &packet, 8); // Copy first 8 bytes (without CRC)
    packet.crc = calculateCRC8(data, 8); // Compute CRC
}
