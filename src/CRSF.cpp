#include "CRSF.h"

CRSF::CRSF() {
    channels.resize(16, 992); // Initialize all channels to neutral value

    // Define key mappings for control inputs
    keyMap['w'] = 0;  // Throttle (Channel 0)
    keyMap['s'] = 0;
    keyMap['a'] = 1;  // Roll (Channel 1)
    keyMap['d'] = 1;
}

void CRSF::mapKeyToChannel(char key) {
    if (keyMap.find(key) != keyMap.end()) {
        int channel = keyMap[key];
        if (key == 'w') channels[channel] = 1092;  // Increase throttle
        if (key == 's') channels[channel] = 892;   // Decrease throttle
        if (key == 'a') channels[channel] = 892;   // Roll left
        if (key == 'd') channels[channel] = 1092;  // Roll right
    }
}

uint8_t CRSF::calculateCRC8(const std::vector<uint8_t> &data) {
    uint8_t crc = 0;
    for (uint8_t byte : data) {
        crc ^= byte;
        for (uint8_t j = 0; j < 8; j++) {
            crc = (crc & 0x80) ? (crc << 1) ^ CRSF_CRC8_POLY : (crc << 1);
        }
    }
    return crc;
}

std::vector<uint16_t> CRSF::getChannels() const {
    return channels;
}
