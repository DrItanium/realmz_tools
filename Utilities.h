//
// Created by jwscoggins on 10/5/20.
//

#ifndef REALMZ_TOOLS_UTILITIES_H
#define REALMZ_TOOLS_UTILITIES_H
#include <cstdint>
#include <type_traits>

namespace realmz {

    /**
     * @brief Is the given value in between a minimum and maximum
     * @tparam T The type to use for comparison
     * @param value The value to see if is range
     * @param minimum The minimum value of the range to check
     * @param maximum The maximum value of the range to check
     * @return True if the given value is in-between (or equal to) the minimum and maximum value.
     */
    template<typename T>
    constexpr bool twixt(T value, T minimum, T maximum) noexcept {
        return ((minimum <= value) && value <= maximum);
    }

    /**
     * @brief Pin a given value into a provided range, if the value is less than min it is min, if it is greater than max then it is max. Optionally,
     * you can cast the inputs to a different types before performing the comparisons itself
     * @tparam T The type of value, min, and max
     * @tparam CompareAs The type to cast value, min, and max to when performing the range comparisons
     * @param value The value to check
     * @param min  The smallest possible value
     * @param max  The largest possible value
     * @return The provided value pinned to the range specified
     */
    template<typename T, typename CompareAs = T>
    constexpr T pin(T value, T min, T max) noexcept {
        if (static_cast<CompareAs>(value) < static_cast<CompareAs>(min)) {
            value = min;
        }
        if (static_cast<CompareAs>(max) < static_cast<CompareAs>(value)) {
            value = max;
        }
        return value;
    }
    struct ConstructInt64 { constexpr ConstructInt64() = default; };
    struct ConstructInt32 { constexpr ConstructInt32() = default; };
    //template<typename T, std::enable_if_t<std::is_integral_v<std::decay_t<T>>, int> = 0> struct ConstructType { };
    constexpr uint64_t make(uint16_t a, uint16_t b, uint16_t c, uint16_t d, ConstructInt64) noexcept {
        return (static_cast<uint64_t>(a) & 0x0000'0000'0000'FFFF) |
                ((static_cast<uint64_t>(b) << 16) & 0x0000'0000'FFFF'0000) |
                ((static_cast<uint64_t>(c) << 32) & 0x0000'FFFF'0000'0000) |
                ((static_cast<uint64_t>(d) << 48) & 0xFFFF'0000'0000'0000);
    }

    static_assert(make(0x6789,0x2345,0xef01,0xabcd, ConstructInt64{}) == 0xABCDEF0123456789);

    constexpr uint32_t make(uint16_t a, uint16_t b, ConstructInt32) noexcept {
        return (static_cast<uint32_t>(a) & 0xFFFF) | ((static_cast<uint32_t>(b) << 16) & 0xFFFF'0000);
    }

} // end namespace realmz
#endif //REALMZ_TOOLS_UTILITIES_H
