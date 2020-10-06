//
// Created by jwscoggins on 10/5/20.
//

#ifndef REALMZ_TOOLS_UTILITIES_H
#define REALMZ_TOOLS_UTILITIES_H

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

} // end namespace realmz
#endif //REALMZ_TOOLS_UTILITIES_H
