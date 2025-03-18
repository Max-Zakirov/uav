#pragma once

#include <array>
#include <stdint.h>

#define PROTOCOL_TYPE_CRSF 0x01

class CeglePacket {
public:
    CeglePacket();
    CeglePacket(uint8_t protocolType, char key);
    
    ~CeglePacket();

    CeglePacket pack(std::array<uint8_t, 2> data);

    std::array<uint8_t, 2> unpack();
    
    private:
    uint8_t protocolType;
    char key;
};