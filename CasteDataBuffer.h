//
// Created by jwscoggins on 9/20/20.
//

#ifndef REALMZ_TOOLS_CASTEDATABUFFER_H
#define REALMZ_TOOLS_CASTEDATABUFFER_H
#include <array>
#include <cstdint>
namespace realmz {
    /**
     * @brief When translating from the old format we have to operate on int16_t's
     */
    using CasteDataBuffer = std::array<int16_t, 576 / 2>;
} // end namespace realmz


#endif //REALMZ_TOOLS_CASTEDATABUFFER_H
