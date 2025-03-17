#ifndef CRSF_H
#define CRSF_H

#include <vector>
#include <cstdint>
#include <unordered_map>

class CRSF {
public:
    static constexpr uint8_t CRSF_CRC8_POLY = 0xD5;

    CRSF();

    void mapKeyToChannel(char key);  // Maps keyboard input to CRSF channels
    uint8_t calculateCRC8(const std::vector<uint8_t> &data);  // CRC computation
    std::vector<uint16_t> getChannels() const;  // Get channel values

private:
    std::vector<uint16_t> channels;
    std::unordered_map<char, int> keyMap;  // Maps keys to channels
};

#endif // CRSF_H
