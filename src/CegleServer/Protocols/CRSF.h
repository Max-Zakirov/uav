#pragma once

#include <cstdint>
#include <unordered_map>
#include <array>
#include <vector>
#include <unistd.h>

#define CRSF_SIZE 26
#define CRSF_PAYLOAD_SIZE 24
#define CRSF_RC_PACKET 0x16
#define CRSF_TX_ADDR 0xC8
#define CRSF_RX_ADDR 0xEC

class CRSF {
public:
    static constexpr uint8_t CRSF_CRC8_POLY = 0xD5;

    CRSF();
    void mapKeyToChannel(char key);  // Maps keyboard input to CRSF channels
    uint8_t computeCRC(const uint8_t* data, size_t length);  // CRC computation
    std::vector<int> getChannels() const;  // Get channel values
    
    std::array<uint8_t, CRSF_SIZE> unpack();
private:
    std::vector<int> channels;
    std::unordered_map<char, int> keyMap;  // Maps keys to channels
};