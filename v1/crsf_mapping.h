#ifndef CRSF_MAPPING_H
#define CRSF_MAPPING_H

#include <cstdint>
#include "crc8.h" // Include CRC8

// CRSF Packet Structure
struct CRSFPacket {
    uint8_t header = 0xC8;  // CRSF Frame Header
    uint8_t length = 9;     // 8 bytes payload + 1 byte CRC
    uint8_t type = 0x16;    // CRSF Channel Data Packet
    uint16_t channels[4] = {992, 992, 992, 992}; // Default (Neutral)
    uint8_t crc;            // CRC checksum
};

// Function to map keys to CRSF values
void mapKeyToCRSF(char key, CRSFPacket &packet);

// Function to compute CRC before sending
void addCRCToPacket(CRSFPacket &packet);

#endif
