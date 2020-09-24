//
// Created by jwscoggins on 9/20/20.
//

#ifndef REALMZ_TOOLS_DRVADJUSTMENTS_H
#define REALMZ_TOOLS_DRVADJUSTMENTS_H
#include <cstdint>
#include <iostream>
#include "CasteDataBuffer.h"
#include "RaceDataBuffer.h"

namespace realmz {
    class DRVAdjustments {
    public:
        explicit DRVAdjustments(const realmz::CasteDataBuffer &buf);
        explicit DRVAdjustments(const realmz::RaceDataBuffer& buf);
        void print(std::ostream &os) const noexcept;
#define X(capital, lowercase) \
        [[nodiscard]] constexpr auto get ## capital () const noexcept { return _ ## lowercase ; }
        X(Charm, charm);
        X(Heat, heat);
        X(Cold, cold);
        X(Electric, electric);
        X(Chemical, chemical);
        X(Mental, mental);
        X(Magical, magical);
#undef X
    private:
        int _charm = 0;
        int _heat = 0;
        int _cold = 0;
        int _electric = 0;
        int _chemical = 0;
        int _mental = 0;
        int _magical = 0;
    };
}
std::ostream &operator<<(std::ostream &os, const realmz::DRVAdjustments &drv) noexcept;
#endif //REALMZ_TOOLS_DRVADJUSTMENTS_H
