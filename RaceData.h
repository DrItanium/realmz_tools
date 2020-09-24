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
    class AgeModifiers {
    public:
        constexpr AgeModifiers(char brawn = 0, char knowledge = 0, char judgment = 0, char agility = 0, char vitality = 0, char luck = 0, char magicResist = 0, char movement = 0,
                     char charm = 0, char heat = 0, char cold = 0, char electrical = 0, char chemical = 0, char mental = 0, char magical = 0) noexcept
        : _brawn(brawn), _knowledge(knowledge), _judgment(judgment), _agility(agility), _vitality(vitality), _luck(luck),
        _magicResist(magicResist), _movement(movement), _charm(charm), _heat(heat), _cold(cold), _electrical(electrical),
        _chemical(chemical), _mental(mental), _magical(magical) {}
        [[nodiscard]] constexpr char getBrawn() const noexcept { return _brawn; }
        [[nodiscard]] constexpr char getKnowledge() const noexcept { return _knowledge; }
        [[nodiscard]] constexpr char getJudgment() const noexcept { return _judgment; }
        [[nodiscard]] constexpr char getAgility() const noexcept { return _agility; }
        [[nodiscard]] constexpr char getVitality() const noexcept { return _vitality; }
        [[nodiscard]] constexpr char getLuck() const noexcept { return _luck; }
        [[nodiscard]] constexpr char getMagicResist() const noexcept { return _magicResist; }
        [[nodiscard]] constexpr char getMovement() const noexcept { return _movement; }
        [[nodiscard]] constexpr char getCharm() const noexcept { return _charm; }
        [[nodiscard]] constexpr char getHeat() const noexcept { return _heat; }
        [[nodiscard]] constexpr char getCold() const noexcept { return _cold; }
        [[nodiscard]] constexpr char getElectrical() const noexcept { return _electrical; }
        [[nodiscard]] constexpr char getChemical() const noexcept { return _chemical; }
        [[nodiscard]] constexpr char getMental() const noexcept { return _mental; }
        [[nodiscard]] constexpr char getMagical() const noexcept { return _magical; }
    private:
        char _brawn = 0;
        char _knowledge = 0;
        char _judgment = 0;
        char _agility = 0;
        char _vitality = 0;
        char _luck = 0;
        char _magicResist = 0;
        char _movement = 0;
        char _charm = 0;
        char _heat = 0;
        char _cold = 0;
        char _electrical = 0;
        char _chemical = 0;
        char _mental = 0;
        char _magical = 0;
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
        bool _canRegenerate = false;
        int _portraitId = 0;
        int _ineligibilityBits = 0;
        uint8_t _flags[30] = { 0 };
        AgeRange _ageRanges[5] = { 0 };
        AgeModifiers _ageModifiers[5] = { 0 };
        int64_t _allowedBits = 0;
    };
}

#endif //REALMZ_TOOLS_RACEDATA_H
