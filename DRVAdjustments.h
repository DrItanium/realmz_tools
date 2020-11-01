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
        explicit constexpr DRVAdjustments(int charm,
                                          int heat,
                                          int cold,
                                          int electric,
                                          int chemical,
                                          int mental,
                                          int magical,
                                          int special) noexcept :
                                          _charm(charm),
                                          _heat(heat),
                                          _cold(cold),
                                          _electric(electric),
                                          _chemical(chemical),
                                          _mental(mental),
                                          _magical(magical),
                                          _special(special) { }
        explicit DRVAdjustments(const realmz::CasteDataBuffer &buf);
        explicit DRVAdjustments(const realmz::RaceDataBuffer& buf);
        void print(std::ostream &os) const noexcept;
        [[nodiscard]] constexpr auto getCharm() const noexcept { return _charm; }
        [[nodiscard]] constexpr auto getHeat() const noexcept { return _heat; }
        [[nodiscard]] constexpr auto getCold() const noexcept { return _cold; }
        [[nodiscard]] constexpr auto getElectric() const noexcept { return _electric; }
        [[nodiscard]] constexpr auto getChemical() const noexcept { return _chemical; }
        [[nodiscard]] constexpr auto getMental() const noexcept { return _mental; }
        [[nodiscard]] constexpr auto getMagical() const noexcept { return _magical; }
        [[nodiscard]] constexpr auto getSpecial() const noexcept { return _special; }
    private:
        int _charm = 0;
        int _heat = 0;
        int _cold = 0;
        int _electric = 0;
        int _chemical = 0;
        int _mental = 0;
        int _magical = 0;
        int _special = 0;
    };
}
std::ostream &operator<<(std::ostream &os, const realmz::DRVAdjustments &drv) noexcept;
#endif //REALMZ_TOOLS_DRVADJUSTMENTS_H
