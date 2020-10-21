//
// Created by jwscoggins on 9/20/20.
//

#include "SpecialAbilities.h"
#include "Caste.h"
#include "AgeGroup.h"
#include "DRVAdjustments.h"

namespace realmz {

    DRVAdjustments::DRVAdjustments(const CasteDataBuffer &buf) : DRVAdjustments(buf[28], buf[29], buf[30], buf[31], buf[32], buf[33], buf[34]) { }
    DRVAdjustments::DRVAdjustments(const RaceDataBuffer &buf) : DRVAdjustments(buf[22], buf[23], buf[24], buf[25], buf[26], buf[27], buf[28]) { }

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
