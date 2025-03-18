#include "CeglePacket.h"

CeglePacket::CeglePacket() {
    protocolType = PROTOCOL_TYPE_CRSF;
    key = 0;
}

CeglePacket::CeglePacket(uint8_t protocolType, char key) {
    protocolType = protocolType;
    key = key;
}

CeglePacket CeglePacket::pack(std::array<uint8_t, 2> data) {
    CeglePacket packet;
    packet.protocolType = data[0];
    packet.key = static_cast<char>(data[1]);
    return packet;
}

std::array<uint8_t, 2> CeglePacket::unpack() {
    std::array<uint8_t, 2> packet;
    packet[0] = protocolType;
    packet[1] = static_cast<uint8_t>(key);
    return packet;
}