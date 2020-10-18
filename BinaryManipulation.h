//
// Created by jwscoggins on 9/20/20.
//

#ifndef REALMZ_TOOLS_BINARYMANIPULATION_H
#define REALMZ_TOOLS_BINARYMANIPULATION_H
#include <cstdint>
namespace realmz {
    constexpr int16_t make(uint8_t first, uint8_t second) noexcept {
        return (static_cast<int16_t>(first) << 8) | (static_cast<int16_t>(second));
    }
    constexpr int8_t upperHalf(int16_t value) noexcept {
        return (value >> 8) & 0xFF;
    }

}
#endif //REALMZ_TOOLS_BINARYMANIPULATION_H
