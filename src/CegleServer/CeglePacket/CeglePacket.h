#pragma once

#include <array>
#include <stdint.h>

#define PROTOCOL_TYPE_CRSF 0x01
#define PACKET_SIZE 2
#define MAX_PACKET_SIZE 1024

class CeglePacket {
public:
    CeglePacket();
    CeglePacket(uint8_t protocolType, char key);
    
    ~CeglePacket();

    static CeglePacket pack(std::array<uint8_t, PACKET_SIZE> data);

    std::array<uint8_t, PACKET_SIZE> unpack();
    
    private:
    uint8_t protocolType;
    char key;
};