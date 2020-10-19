//
// Created by jwscoggins on 9/20/20.
//

#ifndef REALMZ_TOOLS_CASTE_H
#define REALMZ_TOOLS_CASTE_H
#include <iostream>
#include <cstdint>
#include <optional>
#include <array>
#include <vector>
#include <filesystem>
#include "Ability.h"
#include "CasteDataBuffer.h"
#include "CasteConditions.h"
#include "SpecialAbilities.h"
#include "DRVAdjustments.h"
#include "Attributes.h"

namespace realmz {

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
        Done,
    };

    class SpellClassInfo {
    public:
        constexpr SpellClassInfo(bool enabled, int startingLevel, int maxLevelSpells) : _enabled(enabled), _startingLevel(startingLevel),
                                                                                        _maxLevelSpells(maxLevelSpells) {}
        [[nodiscard]] constexpr auto isEnabled() const noexcept { return _enabled; }
        [[nodiscard]] constexpr auto getStartingLevel() const noexcept { return _startingLevel; }
        [[nodiscard]] constexpr auto getMaxLevelSpells() const noexcept { return _maxLevelSpells; }
        void print(std::ostream &out) const noexcept;
    private:
        bool _enabled = false;
        int _startingLevel = 0;
        int _maxLevelSpells = 0;
    };


    struct SpellCastingAbilities {
    public:
        explicit SpellCastingAbilities(const CasteDataBuffer &buf);
        [[nodiscard]] const SpellClassInfo &getSorcererInfo() const noexcept { return _sorcerer; }
        [[nodiscard]] const SpellClassInfo &getPriestInfo() const noexcept { return _priest; }
        [[nodiscard]] const SpellClassInfo &getEnchanterInfo() const noexcept { return _enchanter; }
        [[nodiscard]] const SpellClassInfo &getUnusedInfo() const noexcept { return _unused; }
        [[nodiscard]] constexpr bool canCastSpells() const noexcept {
            return _sorcerer.isEnabled() || _priest.isEnabled() || _enchanter.isEnabled() || _unused.isEnabled();
        }
        [[nodiscard]] constexpr bool supportsSorcererSpellClass() const noexcept { return _sorcerer.isEnabled(); }
        [[nodiscard]] constexpr bool supportsPriestSpellClass() const noexcept { return _priest.isEnabled(); }
        [[nodiscard]] constexpr bool supportsEnchanterSpellClass() const noexcept { return _enchanter.isEnabled(); }
        [[nodiscard]] constexpr bool supportsUnusedSpellClass() const noexcept { return _unused.isEnabled(); }
        [[nodiscard]] constexpr auto getStartingLevel() const noexcept {
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
        [[nodiscard]] constexpr auto getMaxLevelSpells() const noexcept {
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
    constexpr bool legalValue(AgeGroup g) noexcept {
        switch(g) {
            case AgeGroup::Young:
            case AgeGroup::Youth:
            case AgeGroup::Prime:
            case AgeGroup::Adult:
            case AgeGroup::Senior:
                return true;
            default:
                return false;
        }
    }
    enum class BonusAttacksStyle {
        None = 0,
        OneHalf = 1,
        One,
        OneAndOneHalf,
        Two,
    };
    class VictoryPoints {
    public:
        explicit VictoryPoints(const CasteDataBuffer& buf);
        [[nodiscard]] int32_t getVictoryPointsAtLevel(int level) const noexcept;
        void print(std::ostream& os) const noexcept;
        [[nodiscard]] auto size() const noexcept { return _contents.size(); }
    private:
        std::vector<int32_t> _contents;
    };
    class Caste {
    public:
        explicit Caste(const CasteDataBuffer &buffer);
        void print(std::ostream &os) const noexcept;
        [[nodiscard]] const SpecialAbilities& getInitialAbilities() const noexcept { return _initial; }
        [[nodiscard]] const DRVAdjustments& getDRVs() const noexcept { return _drvs; }
        [[nodiscard]] const Attributes& getAttributes() const noexcept { return _attributes; }
        [[nodiscard]] const SpellCastingAbilities& getSpellCasting() const noexcept { return _spellCasting; }
        [[nodiscard]] const CasteConditions& getConditions() const noexcept { return _conditions; }
        [[nodiscard]] constexpr auto canUseMissileWeapons() const noexcept { return _canUseMissileWeapons; }
        [[nodiscard]] constexpr auto getsMissileBonusDamage() const noexcept { return _getsMissileBonusDamage; }
        [[nodiscard]] const Ability& getStamina() const noexcept { return _stamina; }
        [[nodiscard]] const Ability& getDodgeMissile() const noexcept { return _dodgeMissile; }
        [[nodiscard]] const Ability& getMeleeAttack() const noexcept { return _meleeAttack; }
        [[nodiscard]] const Ability& getMissileAttack() const noexcept { return _missileAttack; }
        [[nodiscard]] const Ability& getHandToHand() const noexcept { return _handToHand; }
        [[nodiscard]] constexpr auto getAgeGroup() const noexcept { return _startingAgeGroup; }
        [[nodiscard]] constexpr int getMovementPoints() const noexcept { return _movementPoints; }
        [[nodiscard]] constexpr int getMagicResistance() const noexcept { return _magicResistance; }
        [[nodiscard]] constexpr int getTwoHandedAdjust() const noexcept { return _twoHandedAdjust; }
        [[nodiscard]] constexpr int getMaxStaminaBonus() const noexcept { return _maxStaminaBonus; }
        [[nodiscard]] constexpr BonusAttacksStyle getBonusAttacks() const noexcept { return _bonusAttacks; }
        [[nodiscard]] constexpr int getMaxAttacksPerRound() const noexcept { return _maxAttacksPerRound; }
        [[nodiscard]] const VictoryPoints& getVictoryPointsAtLevel() const noexcept { return _victoryPointsAtLevel; }
        [[nodiscard]] constexpr auto getInitialGoldAmount() const noexcept { return _initialGoldAmount; }
    private:
        SpecialAbilities _initial;
        DRVAdjustments _drvs;
        Attributes _attributes;
        SpellCastingAbilities _spellCasting;
        CasteConditions _conditions;
        bool _canUseMissileWeapons = false;
        bool _getsMissileBonusDamage = false;
        Ability _stamina;
        Ability _dodgeMissile;
        Ability _meleeAttack;
        Ability _missileAttack;
        Ability _handToHand;
        int _inelegibilityIndex = 0;
        AgeGroup _startingAgeGroup = AgeGroup::None;
        int _movementPoints = 0;
        int _magicResistance = 0;
        int _twoHandedAdjust = 0;
        int _maxStaminaBonus = 0;
        BonusAttacksStyle _bonusAttacks = BonusAttacksStyle::None;
        int _maxAttacksPerRound = 0;

        VictoryPoints _victoryPointsAtLevel;
        int _initialGoldAmount = 0;
        std::vector<int> _initialItems;
        int64_t _allowedBits = 0; // originally two 32-bit numbers with bits [0,57] being used
        int _castePortraitIndex = 0;
    };
    void setCasteDataLocation(const std::filesystem::path& path) noexcept;
    bool casteDataLocationSet() noexcept;
    const Caste& loadCaste(CasteKind ck);

} // end namespace realmz
std::ostream& operator<<(std::ostream& os, const realmz::Caste& caste) noexcept;
std::ostream& operator<<(std::ostream& os, realmz::CasteKind ck) noexcept;
std::ostream& operator<<(std::ostream& os, realmz::BonusAttacksStyle group) noexcept;
std::ostream& operator<<(std::ostream& os, const realmz::SpellCastingAbilities& sci) noexcept;
std::ostream &operator<<(std::ostream &os, realmz::AgeGroup group) noexcept;
std::ostream & operator<<(std::ostream &os, const realmz::SpellClassInfo &sci) noexcept;
std::ostream& operator<<(std::ostream& os, const realmz::VictoryPoints& vp) noexcept;
#endif //REALMZ_TOOLS_CASTE_H
