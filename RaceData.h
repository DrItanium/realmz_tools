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
    enum class RaceKind : uint16_t {
        Human,
        ShadowElf,
        Elf,
        Orc,
        Furfoot,
        Gnome,
        Dwarf,
        HalfElf,
        HalfOrc,
        Goblin,
        Hobgoblin,
        Kobold,
        Vampire,
        LizardMan,
        Brownie,
        Pixie,
        Leprechaun,
        Demon,
        Cathoon,
        Done,
    };
    /**
     * @brief Realmz calls the attack versus other races "race hatred"...odd
     */
    class Hatred {
    public:
        explicit Hatred(const RaceDataBuffer& buffer);
        explicit constexpr Hatred(int vsMagic = 0,
                                  int vsUndead = 0,
                                  int vsDemonic = 0,
                                  int vsReptilian = 0,
                                  int vsVeryEvil = 0,
                                  int vsIntelligent = 0,
                                  int vsGiantSized = 0,
                                  int vsNonHumanoid = 0) noexcept :
        _hitMagicUsing(vsMagic),
        _hitUndead(vsUndead),
        _hitDemonic(vsDemonic),
        _hitReptilian(vsReptilian),
        _hitVeryEvil(vsVeryEvil),
        _hitIntelligent(vsIntelligent),
        _hitGiantSize(vsGiantSized),
        _hitNonHumanoid(vsNonHumanoid) { }
        [[nodiscard]] constexpr auto getHitVsMagicUsing() const noexcept { return _hitMagicUsing; }
        [[nodiscard]] constexpr auto getHitVsUndead() const noexcept { return _hitUndead; }
        [[nodiscard]] constexpr auto getHitVsDemonic() const noexcept { return _hitDemonic; }
        [[nodiscard]] constexpr auto getHitVsReptilian() const noexcept { return _hitReptilian; }
        [[nodiscard]] constexpr auto getHitVsVeryEvil() const noexcept { return _hitVeryEvil; }
        [[nodiscard]] constexpr auto getHitVsIntelligent() const noexcept { return _hitIntelligent; }
        [[nodiscard]] constexpr auto getHitGiantSize() const noexcept { return _hitGiantSize; }
        [[nodiscard]] constexpr auto getHitNonHumanoid() const noexcept { return _hitNonHumanoid; }
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
        constexpr explicit AgeRange(int from = 0, int to = 0) : _from(from), _to(to) { }
        [[nodiscard]] constexpr auto getFrom() const noexcept { return _from; }
        [[nodiscard]] constexpr auto getTo() const noexcept { return _to; }
    private:
        int _from = 0;
        int _to = 0;
    };
    class AgeModifiers {
    public:
        constexpr explicit AgeModifiers(char brawn = 0, char knowledge = 0, char judgment = 0, char agility = 0, char vitality = 0, char luck = 0, char magicResist = 0, char movement = 0,
                     char charm = 0, char heat = 0, char cold = 0, char electrical = 0, char chemical = 0, char mental = 0, char magical = 0) noexcept
        : _brawn(brawn), _knowledge(knowledge), _judgment(judgment), _agility(agility), _vitality(vitality), _luck(luck),
        _magicResist(magicResist), _movement(movement), _charm(charm), _heat(heat), _cold(cold), _electrical(electrical),
        _chemical(chemical), _mental(mental), _magical(magical) {}
        [[nodiscard]] constexpr auto getBrawn() const noexcept { return _brawn; }
        [[nodiscard]] constexpr auto getKnowledge() const noexcept { return _knowledge; }
        [[nodiscard]] constexpr auto getJudgment() const noexcept { return _judgment; }
        [[nodiscard]] constexpr auto getAgility() const noexcept { return _agility; }
        [[nodiscard]] constexpr auto getVitality() const noexcept { return _vitality; }
        [[nodiscard]] constexpr auto getLuck() const noexcept { return _luck; }
        [[nodiscard]] constexpr auto getMagicResist() const noexcept { return _magicResist; }
        [[nodiscard]] constexpr auto getMovement() const noexcept { return _movement; }
        [[nodiscard]] constexpr auto getCharm() const noexcept { return _charm; }
        [[nodiscard]] constexpr auto getHeat() const noexcept { return _heat; }
        [[nodiscard]] constexpr auto getCold() const noexcept { return _cold; }
        [[nodiscard]] constexpr auto getElectrical() const noexcept { return _electrical; }
        [[nodiscard]] constexpr auto getChemical() const noexcept { return _chemical; }
        [[nodiscard]] constexpr auto getMental() const noexcept { return _mental; }
        [[nodiscard]] constexpr auto getMagical() const noexcept { return _magical; }
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
        explicit RaceData(const RaceDataBuffer& buf);
        [[nodiscard]] const Hatred& getRaceHatredStats() const noexcept { return _hatred; }
        [[nodiscard]] const SpecialAbilities& getSpecialAbilities() const noexcept { return _specialAbilities; }
        [[nodiscard]] const DRVAdjustments& getDrvs() const noexcept { return _drvs; }
        [[nodiscard]] const Attributes& getAttributes() const noexcept { return _attributes; }
        [[nodiscard]] constexpr auto getUnused0(size_t index) const noexcept { return _unused0[index & 0b111]; }
        [[nodiscard]] constexpr auto getCondition(size_t index) const noexcept { return _conditions[index >= 40 ? 39 : index]; }
        [[nodiscard]] constexpr auto getUnused1() const noexcept { return _unused1; }
        [[nodiscard]] constexpr auto getUnused2() const noexcept { return _unused2; }
        [[nodiscard]] constexpr auto getBaseMovementPoints() const noexcept { return _baseMovementPoints; }
        [[nodiscard]] constexpr auto getMagicResistance() const noexcept { return _magicResistance; }
        [[nodiscard]] constexpr auto getTwoHandedAdjustment() const noexcept { return _twoHandedAdjustment; }
        [[nodiscard]] constexpr auto getMissileWeaponAdjust() const noexcept { return _missileWeaponAdjust; }
        [[nodiscard]] constexpr auto getAttacksPerRound() const noexcept { return _attacksPerRound; }
        [[nodiscard]] constexpr auto getMaxAttacksPerRound() const noexcept { return _maxAttacksPerRound; }
        [[nodiscard]] constexpr auto canRegenerate() const noexcept { return _canRegenerate; }
        [[nodiscard]] constexpr auto getPortraitId() const noexcept { return _portraitId; }
        [[nodiscard]] constexpr auto getIneligibilityBits() const noexcept { return _ineligibilityBits; }
        [[nodiscard]] constexpr auto getAllowedBits() const noexcept { return _allowedBits; }
        [[nodiscard]] constexpr auto getFlags(size_t index) const noexcept { return _flags[index >= 30 ? 29 : index]; }
        [[nodiscard]] const AgeRange& getAgeRange(size_t index) const noexcept {return _ageRanges[index < 5 ? index : 4]; }
        [[nodiscard]] const AgeModifiers& getAgeModifier(size_t index) const noexcept {return _ageModifiers[index < 5 ? index : 4]; }
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
        AgeRange _ageRanges[5];
        AgeModifiers _ageModifiers[5];
        int64_t _allowedBits = 0;
    };
    void setRaceDataLocation(const std::filesystem::path& path) noexcept;
    bool raceDataLocationSet() noexcept;
    const RaceData& loadRaceData(realmz::RaceKind kind);
}
std::ostream& operator<<(std::ostream &os, realmz::RaceKind r) noexcept;

#endif //REALMZ_TOOLS_RACEDATA_H
