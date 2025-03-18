#ifndef CEGLA_PACKET_H
#define CEGLA_PACKET_H

#include <vector>
#include <cstdint>

class CegLaPacket {
public:
    uint8_t address; 
    //uint8_t length; 
    uint8_t type;
    std::vector<uint8_t> payload;
    //uint8_t crc;

    CegLaPacket(uint8_t address, uint8_t type, std::vector<uint8_t>& data);

    std::vector<uint8_t> pack() const;
    bool unpack(const std::vector<uint8_t>& data);
    static uint8_t calculateCRC8(const std::vector<uint8_t>& data);
};

#endif // CEGLA_PACKET_H