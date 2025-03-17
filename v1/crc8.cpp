#include "crc8.h"

// Polynomial for CRSF CRC8
#define CRSF_CRC8_POLY 0xD5

uint8_t calculateCRC8(const uint8_t *data, uint8_t length) {
    uint8_t crc = 0;
    for (uint8_t i = 0; i < length; i++) {
        crc ^= data[i];
        for (uint8_t j = 0; j < 8; j++) {
            if (crc & 0x80) {
                crc = (crc << 1) ^ CRSF_CRC8_POLY;
            } else {
                crc <<= 1;
            }
        }
    }
    return crc;
}
