//
// Created by jwscoggins on 9/20/20.
//

#include "SpecialAbilities.h"
#include "Caste.h"
#include "DRVAdjustments.h"

namespace realmz {

    DRVAdjustments::DRVAdjustments(const CasteDataBuffer &buf) : _charm(buf[28]), _heat(buf[29]), _cold(buf[30]), _electric(buf[31]), _chemical(buf[32]), _mental(buf[33]), _magical(buf[34]) {}
    DRVAdjustments::DRVAdjustments(const RaceDataBuffer &buf) : _charm(buf[22]), _heat(buf[23]), _cold(buf[24]), _electric(buf[25]), _chemical(buf[26]), _mental(buf[27]), _magical(buf[28]) { }

    void
    DRVAdjustments::print(std::ostream &os) const noexcept {
#define X(field) \
            os << #field << ": " << _ ## field << std::endl
        X(charm);
        X(heat);
        X(cold);
        X(electric);
        X(chemical);
        X(mental);
        X(magical);
#undef X
    }
}

std::ostream&
operator<<(std::ostream &os, const realmz::DRVAdjustments &drv) noexcept {
    drv.print(os);
    return os;
}
