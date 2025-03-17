#include "CegLaPacket.h"
#include <iostream>


CegLaPacket::CegLaPacket(uint8_t address, uint8_t type, std::vector<uint8_t>& data) 
    : address(address), type(type), payload(payload) {}

