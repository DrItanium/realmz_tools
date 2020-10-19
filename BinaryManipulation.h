//
// Created by jwscoggins on 9/20/20.
//

#ifndef REALMZ_TOOLS_BINARYMANIPULATION_H
#define REALMZ_TOOLS_BINARYMANIPULATION_H
#include <cstdint>
namespace realmz {
    constexpr uint16_t make(uint8_t first, uint8_t second) noexcept {
        return ((static_cast<uint16_t>(first) << 8u) & 0xFF00) | (static_cast<uint16_t>(second) & 0x00FF);
    }
    constexpr uint8_t upperHalf(uint16_t value) noexcept { return (value >> 8u) & 0xFF; }
    constexpr uint8_t lowerHalf(uint16_t value) noexcept { return static_cast<uint8_t>(value); }

    struct ConstructInt64 { constexpr ConstructInt64() = default; };
    struct ConstructInt32 { constexpr ConstructInt32() = default; };
    //template<typename T, std::enable_if_t<std::is_integral_v<std::decay_t<T>>, int> = 0> struct ConstructType { };
    constexpr uint64_t make(uint16_t a, uint16_t b, uint16_t c, uint16_t d, ConstructInt64) noexcept {
        constexpr uint64_t Masks[] {
                0x0000'0000'0000'FFFF,
                0x0000'0000'FFFF'0000,
                0x0000'FFFF'0000'0000,
                0xFFFF'0000'0000'0000,
        };
        return (static_cast<uint64_t>(a) & Masks[0]) |
               ((static_cast<uint64_t>(b) << 16u) & Masks[1]) |
               ((static_cast<uint64_t>(c) << 32u) & Masks[2]) |
               ((static_cast<uint64_t>(d) << 48u) & Masks[3]);
    }

    static_assert(make(0x6789,0x2345,0xef01,0xabcd, ConstructInt64{}) == 0xABCDEF0123456789);

    constexpr uint32_t make(uint16_t a, uint16_t b, ConstructInt32) noexcept {
        constexpr uint32_t Masks[] {
                0x0000'FFFF,
                0xFFFF'0000,
        };
        return (static_cast<uint32_t>(a) & Masks[0]) | ((static_cast<uint32_t>(b) << 16) & Masks[1]);
    }

}
#endif //REALMZ_TOOLS_BINARYMANIPULATION_H
