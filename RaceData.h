//
// Created by jwscoggins on 9/20/20.
//

#ifndef REALMZ_TOOLS_RACEDATA_H
#define REALMZ_TOOLS_RACEDATA_H
#include <cstdint>
#include <array>
#include "RaceDataBuffer.h"
#include "SpecialAbilities.h"
#include "DRVAdjustments.h"
#include "Attributes.h"
namespace realmz {
    /**
     * @brief Realmz calls the attack versus other races "race hatred"...odd
     */
    class Hatred {
    public:
        Hatred() = default;
        Hatred(const RaceDataBuffer& buffer);
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
    class AgeRange {
    public:
        constexpr AgeRange(int from = 0, int to = 0) : _from(from), _to(to) { }
        constexpr auto getFrom() const noexcept { return _from; }
        constexpr auto getTo() const noexcept { return _to; }
    private:
        int _from = 0;
        int _to = 0;
    };
    /**
     * @brief Holds all of the data for a given race that a character can be
     */
    class RaceData {
    public:
        RaceData(const RaceDataBuffer& buf);
        const Hatred& getRaceHatredStats() const noexcept { return _hatred; }
        const SpecialAbilities& getSpecialAbilities() const noexcept { return _specialAbilities; }
        const DRVAdjustments& getDrvs() const noexcept { return _drvs; }
        const Attributes& getAttributes() const noexcept { return _attributes; }
    private:
        Hatred _hatred;
        SpecialAbilities _specialAbilities;
        DRVAdjustments _drvs;
        Attributes _attributes;
        int _unused0[8] = { 0 };
        int _conditions[40] = { 0 };
        int _unused1 = 0;
        int _unused2 = 0;
        int _baseMovementPoints = 0;
        int _magicResistance = 0;
        int _twoHandedAdjustment = 0;
        int _missileWeaponAdjust = 0;
        int _attacksPerRound = 0;
        int _maxAttacksPerRound = 0;
        uint8_t _flags[30] = { 0 };
        AgeRange _ageRanges[5] = { 0 };

    };
}

#endif //REALMZ_TOOLS_RACEDATA_H
