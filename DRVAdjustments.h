//
// Created by jwscoggins on 9/20/20.
//

#ifndef REALMZ_TOOLS_DRVADJUSTMENTS_H
#define REALMZ_TOOLS_DRVADJUSTMENTS_H
#include <cstdint>
#include <iostream>
#include "CasteDataBuffer.h"

namespace realmz {
    struct DRVAdjustments {
        int _charm = 0;
        int _heat = 0;
        int _cold = 0;
        int _electric = 0;
        int _chemical = 0;
        int _mental = 0;
        int _magical = 0;
        DRVAdjustments(const realmz::CasteDataBuffer &buf);
        void print(std::ostream &os) const noexcept;
    };
}
std::ostream &operator<<(std::ostream &os, const realmz::DRVAdjustments &drv) noexcept;
#endif //REALMZ_TOOLS_DRVADJUSTMENTS_H
