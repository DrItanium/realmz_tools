//
// Created by jwscoggins on 9/20/20.
//

#ifndef REALMZ_TOOLS_CASTE_H
#define REALMZ_TOOLS_CASTE_H
#include <iostream>
#include <cstdint>
#include <optional>
#include <array>
#include "Ability.h"

namespace realmz {
    /**
     * @brief When translating from the old format we have to operate on int16_t's
     */
    using DataBuffer = std::array<int16_t, 576 / 2>;

    /**
     * @brief The kind of caste we are currently looking at
     */
    enum class CasteKind {
        Fighter = 0,
        Monk,
        Crusader,
        Archer,
        Rogue,
        Sorcerer,
        Priest,
        Enchanter,
        Evoker,
        Cardinal,
        Cabalist,
        Berzerker,
        Bard,
        Fencer,
        Marksman,
        Assassin,
        Dabbler,
        BattleMage,
        Warlock,
        Minstrel,
    };

    class Attribute {
    public:
        constexpr Attribute(int min, int max, int adjustment) : _min(min), _max(max), _adjustment(adjustment) {}
        constexpr auto getMin() const noexcept { return _min; }
        constexpr auto getMax() const noexcept { return _max; }
        constexpr auto getAdjustment() const noexcept { return _adjustment; }
        void print(std::ostream& os) const noexcept;
    private:
        int _min = 3;
        int _max = 25;
        int _adjustment = 0;
    };

    struct SpecialAbilities {
        Ability _sneakAttack;
        Ability _majorWound;
        Ability _detectSecret;
        Ability _acrobaticAct;
        Ability _detectTrap;
        Ability _disableTrap;
        Ability _forceLock;
        Ability _pickLock;
        Ability _turnUndead;
        SpecialAbilities(const DataBuffer &buf);
        void print(std::ostream& os) const noexcept;

    };


    struct DRVAdjustments {
        int _charm;
        int _heat;
        int _cold;
        int _electric;
        int _chemical;
        int _mental;
        int _magical;
        DRVAdjustments(const DataBuffer &buf);
        void print(std::ostream &os) const noexcept;
    };


    struct Attributes {
    public:
        Attribute _brawn;
        Attribute _knowledge;
        Attribute _judgment;
        Attribute _agility;
        Attribute _vitality;
        Attribute _luck;
        Attributes(const DataBuffer &buf);
        void print(std::ostream &out) const noexcept;
    };


    class SpellClassInfo {
    public:
        constexpr SpellClassInfo(bool enabled, int startingLevel, int maxLevelSpells) : _enabled(enabled), _startingLevel(startingLevel),
                                                                                        _maxLevelSpells(maxLevelSpells) {}
        constexpr auto isEnabled() const noexcept { return _enabled; }
        constexpr auto getStartingLevel() const noexcept { return _startingLevel; }
        constexpr auto getMaxLevelSpells() const noexcept { return _maxLevelSpells; }
        void print(std::ostream &out) const noexcept;
    private:
        bool _enabled = false;
        int _startingLevel = 0;
        int _maxLevelSpells = 0;
    };


    struct SpellCastingAbilities {
    public:
        SpellCastingAbilities(const DataBuffer &buf);
        const SpellClassInfo &getSorcererInfo() const noexcept { return _sorcerer; }
        const SpellClassInfo &getPriestInfo() const noexcept { return _priest; }
        const SpellClassInfo &getEnchanterInfo() const noexcept { return _enchanter; }
        const SpellClassInfo &getUnusedInfo() const noexcept { return _unused; }
        constexpr bool canCastSpells() const noexcept {
            return _sorcerer.isEnabled() || _priest.isEnabled() || _enchanter.isEnabled() || _unused.isEnabled();
        }
        constexpr bool supportsSorcererSpellClass() const noexcept { return _sorcerer.isEnabled(); }
        constexpr bool supportsPriestSpellClass() const noexcept { return _priest.isEnabled(); }
        constexpr bool supportsEnchanterSpellClass() const noexcept { return _enchanter.isEnabled(); }
        constexpr bool supportsUnusedSpellClass() const noexcept { return _unused.isEnabled(); }
        constexpr auto getStartingLevel() const noexcept {
            if (_sorcerer.isEnabled()) {
                return _sorcerer.getStartingLevel();
            } else if (_priest.isEnabled()) {
                return _priest.getStartingLevel();
            } else if (_enchanter.isEnabled()) {
                return _enchanter.getStartingLevel();
            } else if (_unused.isEnabled()) {
                return _unused.getStartingLevel();
            } else {
                return -1;
            }
        }
        constexpr auto getMaxLevelSpells() const noexcept {
            if (_sorcerer.isEnabled()) {
                return _sorcerer.getMaxLevelSpells();
            } else if (_priest.isEnabled()) {
                return _priest.getMaxLevelSpells();
            } else if (_enchanter.isEnabled()) {
                return _enchanter.getMaxLevelSpells();
            } else if (_unused.isEnabled()) {
                return _unused.getMaxLevelSpells();
            } else {
                return -1;
            }
        }
        void print(std::ostream &out) const noexcept;
    private:
        SpellClassInfo _sorcerer;
        SpellClassInfo _priest;
        SpellClassInfo _enchanter;
        SpellClassInfo _unused;
    };

    enum class AgeGroup {
        None = 0,
        Young = 1,
        Youth,
        Prime,
        Adult,
        Senior,
    };
    enum class BonusAttacksStyle {
        None = 0,
        OneHalf = 1,
        One,
        OneAndOneHalf,
        Two,
    };

    class Caste {
    public:
        Caste(const DataBuffer &buffer);
        void print(std::ostream &os) const noexcept;
    private:
        SpecialAbilities _initial;
        DRVAdjustments _drvs;
        Attributes _attributes;
        SpellCastingAbilities _spellCasting;
        bool _canUseMissileWeapons = false;
        bool _getsMissileBonusDamage = false;
        Ability _stamina;
        Ability _dodgeMissile;
        Ability _meleeAttack;
        Ability _missileAttack;
        Ability _handToHand;
        int _creatorCodeId = 0;
        AgeGroup _startingAgeGroup = AgeGroup::None;
        int _movementPoints = 0;
        int _magicResistance = 0;
        int _twoHandedAdjust = 0;
        int _maxStaminaBonus = 0;
        BonusAttacksStyle _bonusAttacks = BonusAttacksStyle::None;
        int _maxAttacksPerRound = 0;
    };

} // end namespace realmz
std::ostream& operator<<(std::ostream& os, const realmz::Caste& caste) noexcept;
std::ostream& operator<<(std::ostream& os, const realmz::Attribute& ca) noexcept;
std::ostream& operator<<(std::ostream& os, realmz::CasteKind ck) noexcept;
std::ostream& operator<<(std::ostream& os, realmz::BonusAttacksStyle group) noexcept;
std::ostream& operator<<(std::ostream& os, const realmz::SpellCastingAbilities& sci) noexcept;
std::ostream &operator<<(std::ostream &os, const realmz::DRVAdjustments &drv) noexcept;
std::ostream &operator<<(std::ostream &os, realmz::AgeGroup group) noexcept;
std::ostream &operator<<(std::ostream &os, const realmz::Attributes &attrib) noexcept;
std::ostream &operator<<(std::ostream &os, const realmz::SpecialAbilities &sa) noexcept;
std::ostream & operator<<(std::ostream &os, const realmz::SpellClassInfo &sci) noexcept;
std::ostream &operator<<(std::ostream &os, const Ability &sa) noexcept;
#endif //REALMZ_TOOLS_CASTE_H
