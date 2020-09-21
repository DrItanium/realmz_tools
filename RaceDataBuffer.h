//
// Created by jwscoggins on 9/20/20.
//

#ifndef REALMZ_TOOLS_RACEDATABUFFER_H
#define REALMZ_TOOLS_RACEDATABUFFER_H
#include <cstdint>
#include <array>

namespace realmz {
    /**
     * @brief Old school realmz race data buffer
     */
    using RaceDataBuffer = std::array<int16_t, 0x198 / 2>;
}

#endif //REALMZ_TOOLS_RACEDATABUFFER_H
