//
// Created by jwscoggins on 9/20/20.
//

#ifndef REALMZ_TOOLS_RACEDATA_H
#define REALMZ_TOOLS_RACEDATA_H
#include <cstdint>
#include <array>
#include "RaceDataBuffer.h"
namespace realmz {
    /**
     * @brief Realmz calls the attack versus other races "race hatred"...odd
     */
    class RaceHatred {
    public:
        RaceHatred() = default;
        RaceHatred(const RaceDataBuffer& buffer);
        constexpr auto getHitVsMagicUsing() const noexcept { return _hitMagicUsing; }
        constexpr auto getHitVsUndead() const noexcept { return _hitUndead; }
        constexpr auto getHitVsDemonic() const noexcept { return _hitDemonic; }
        constexpr auto getHitVsReptilian() const noexcept { return _hitReptilian; }
        constexpr auto getHitVsVeryEvil() const noexcept { return _hitVeryEvil; }
        constexpr auto getHitVsIntelligent() const noexcept { return _hitIntelligent; }
        constexpr auto getHitGiantSize() const noexcept { return _hitGiantSize; }
        constexpr auto getHitNonHumanoid() const noexcept { return _hitNonHumanoid; }
    private:
        int _hitMagicUsing = 0;
        int _hitUndead = 0;
        int _hitDemonic = 0;
        int _hitReptilian = 0;
        int _hitVeryEvil = 0;
        int _hitIntelligent = 0;
        int _hitGiantSize = 0;
        int _hitNonHumanoid = 0;
    };
    /**
     * @brief Holds all of the data for a given race that a character can be
     */
    class RaceData {
    public:
        RaceData(const RaceDataBuffer& buf);
        const RaceHatred& getRaceHatredStats() const noexcept { return _hatred; }
    private:
        RaceHatred _hatred;
    };
}

#endif //REALMZ_TOOLS_RACEDATA_H
