//
// Created by jwscoggins on 10/5/20.
//

#ifndef REALMZ_TOOLS_UTILITIES_H
#define REALMZ_TOOLS_UTILITIES_H
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

} // end namespace realmz
#endif //REALMZ_TOOLS_UTILITIES_H
