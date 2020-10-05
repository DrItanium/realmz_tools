//
// Created by jwscoggins on 10/4/20.
//

#ifndef REALMZ_TOOLS_CHARACTER_H
#define REALMZ_TOOLS_CHARACTER_H
#include <cstdint>
#include <array>
#include <string>
namespace realmz {
    using CharacterDataBuffer = std::array<int16_t, 872/2>;
    class SpecialInfo_CharVersion {
    public:
        SpecialInfo_CharVersion(const CharacterDataBuffer& buffer);
        constexpr int8_t getSneakAttack() const noexcept { return _sneakAttack; }
        constexpr int8_t getCauseMajorWound() const noexcept { return _causeMajorWound; }
        constexpr int8_t getDetectSecret() const noexcept { return _detectSecret; }
        constexpr int8_t getAcrobaticAct() const noexcept { return _acrobaticAct; }
        constexpr int8_t getDetectTrap() const noexcept { return _detectTrap; }
        constexpr int8_t getDisableTrap() const noexcept { return _disableTrap; }
        constexpr int8_t getForceLock() const noexcept { return _forceLock; }
        constexpr int8_t getPickLock() const noexcept { return _pickLock; }
        constexpr int8_t getTurnUndead() const noexcept { return _turnUndead; }
    private:
        int8_t _sneakAttack;
        int8_t _causeMajorWound;
        int8_t _detectSecret;
        int8_t _acrobaticAct;
        int8_t _detectTrap;
        int8_t _disableTrap;
        int8_t _forceLock;
        int8_t _pickLock;
        int8_t _turnUndead;
    };
    class InventoryItem {
    public:
        InventoryItem(int16_t index, uint8_t field2, uint8_t field3, uint16_t flags) : _idx(index), _f2(field2), _f3(field3), _flags(flags) { }
        constexpr auto getIndex() const noexcept { return _idx; }
        constexpr auto getField2() const noexcept { return _f2; }
        constexpr auto getField3() const noexcept { return _f3; }
        constexpr auto getFlags() const noexcept { return _flags; }
    private:
        uint16_t _idx;
        uint8_t _f2;
        uint8_t _f3;
        uint16_t _flags;
    };

    using SpellLevel = std::array<bool, 12>;


    class CharacterConditions {
    public:
        CharacterConditions(const CharacterDataBuffer& buf);
        constexpr int16_t getInRetreat() const noexcept { return _inRetreat; }
        constexpr int16_t getHelpless() const noexcept { return _helpless; }
        constexpr int16_t getTangled() const noexcept { return _tangled; }
        constexpr int16_t getIsCursed() const noexcept { return _isCursed; }
        constexpr int16_t getConditionMagicAura() const noexcept { return _conditionMagicAura; }
        constexpr int16_t getSupidOrSilenced1() const noexcept { return _supidOrSilenced1; }
        constexpr int16_t getIsSlow() const noexcept { return _isSlow; }
        constexpr int16_t getConditionShieldedFromNormalAttacks() const noexcept { return _conditionShieldedFromNormalAttacks; }
        constexpr int16_t getConditionShieldedFromProjectiles() const noexcept { return _conditionShieldedFromProjectiles; }
        constexpr int16_t getPoisoned() const noexcept { return _poisoned; }
        constexpr int16_t getRegenerating() const noexcept { return _regenerating; }
        constexpr int16_t getProtectionFromHeatAttacks() const noexcept { return _protectionFromHeatAttacks; }
        constexpr int16_t getProtectionFromColdAttacks() const noexcept { return _protectionFromColdAttacks; }
        constexpr int16_t getProtectionFromElectricalAttacks() const noexcept { return _protectionFromElectricalAttacks; }
        constexpr int16_t getProtectionFromChemicalAttacks() const noexcept { return _protectionFromChemicalAttacks; }
        constexpr int16_t getProtectionFromMentalAttacks() const noexcept { return _protectionFromMentalAttacks; }
        constexpr int16_t getProtectionFrom1StLevelSpells() const noexcept { return _protectionFrom1stLevelSpells; }
        constexpr int16_t getProtectionFrom2NdLevelSpells() const noexcept { return _protectionFrom2ndLevelSpells; }
        constexpr int16_t getProtectionFrom3ThLevelSpells() const noexcept { return _protectionFrom3thLevelSpells; }
        constexpr int16_t getProtectionFrom4ThLevelSpells() const noexcept { return _protectionFrom4thLevelSpells; }
        constexpr int16_t getProtectionFrom5ThLevelSpells() const noexcept { return _protectionFrom5thLevelSpells; }
    private:
        int16_t _inRetreat;
        int16_t _helpless;
        int16_t _tangled;
        int16_t _isCursed;
        int16_t _conditionMagicAura;
        int16_t _supidOrSilenced1;
        int16_t _isSlow;
        int16_t _conditionShieldedFromNormalAttacks;
        int16_t _conditionShieldedFromProjectiles;
        int16_t _poisoned;
        int16_t _regenerating;
        int16_t _protectionFromHeatAttacks;
        int16_t _protectionFromColdAttacks;
        int16_t _protectionFromElectricalAttacks;
        int16_t _protectionFromChemicalAttacks;
        int16_t _protectionFromMentalAttacks;
        int16_t _protectionFrom1stLevelSpells;
        int16_t _protectionFrom2ndLevelSpells;
        int16_t _protectionFrom3thLevelSpells;
        int16_t _protectionFrom4thLevelSpells;
        int16_t _protectionFrom5thLevelSpells;
    };
    enum class SupportedSpellClass : int16_t {
        None = 0,
        Sorcerer = 1,
        Priest = 2,
        Enchanter = 3,
    };
    enum class Gender : int16_t {
        Undefined,
        Male = 1,
        Female = 2,
    };
    class Character {
    private:
        uint16_t _id;
        int16_t _verifyField0;
        int16_t _chanceToHit;
        int16_t _dodgeMissile;
        int16_t _missileAdjust;
        int16_t _bareHandDamageMax;
        int16_t _allianceClass;
        int16_t _attacksPerRound;
        int16_t _field_0x10;
        int16_t _field_0x12;
        int16_t _field_0x14;
        int16_t _numItems;
        int16_t _field_0x18;
        int16_t _field_0x1a;
        int16_t _field_0x1c;
        int16_t _otherAttacksPerRoundModifier;
        int16_t _vitalityFromItems;
        int16_t _field_0x22;
        int16_t _luckFromItems;
        int16_t _brawnFromItems;
        int16_t _magicResistance;
        int16_t _movementBonus;
        int16_t _armorRating;
        int16_t _damagePlus;
        int16_t _race;
        int16_t _caste;
        SupportedSpellClass _supportedSpellClass;
        Gender _gender;
        int16_t _skillLevel;
        int16_t _field_0x3a;
        int16_t _movementPoints;
        int16_t _combatPoints;
        std::array<int16_t, 7> _totalSpellsRemaining;
        short _staminaCurrent;
        short _staminaTotal;
        short _portraitIndex;
        short _iconPictureIndex;
        short _spellPointsCurrent;
        short _spellPointsTotal;
        short _field_0x5a;
        short _field_0x5c;
        short _field_0x5e;
        short _handToHandMax;
        CharacterConditions _conditions;
        short _strong;
        short _protectionFromFoe;
        short _speed;
        short _invisible;
        short _isAnimated;
        short _stone;
        short _blind;
        short _diseased;
        short _isConfused;
        short _reflectingSpells;
        short _reflectingAttacks;
        short _attackBonus;
        short _absorbEnergy;
        short _absorbSpellEnergyFromAttacks;
        short _field_0xa8;
        short _hinderedAttack;
        short _hinderedDefense;
        short _defensiveBonus;
        short _affectsCastingAbility;
        short _vsMagicUsingCreatures;
        short _vsUndeadCreatures;
        short _vsDemonicCreatures;
        short _vsReptileCreatures;
        short _vsVeryEvilCreatures;
        short _vsIntelligentCreatures;
        short _vsGiantSizedCreatures;
        short _vsNonHumanoidCreature;
        short _equippedItems[20];
        short _field_0xea;
        short _field_0xec;
        short _field_0xee;
        short _field_0xf0;
        SpecialInfo_CharVersion _specialInfo;
        uint8_t _field_0x100;
        uint8_t _field_0x101;
        uint8_t _field_0x102;
        uint8_t _field_0x103;
        uint8_t _field_0x104;
        uint8_t _field_0x105;
        uint8_t _field_0x106;
        uint8_t _field_0x107;
        uint8_t _field_0x108;
        uint8_t _field_0x109;
        uint8_t _field_0x10a;
        uint8_t _field_0x10b;
        short _field_0x10c;
        short _field_0x10e;
        short _damageReductionVsCharm;
        short _damageReductionVsHeat;
        short _damageReductionVsCold;
        short _damageReductionVsElectric;
        short _damageReductionVsChemical;
        short _damageReductionVsMental;
        short _damageReductionVsMagic;
        short _damageReductionVsSpecial;
        short _ageClass;
        short _verifyField1;
        std::array<InventoryItem, 30> _items;
        std::array<int, 5> _anArray;
        int _daysOld;
        int _victoryPoints;
        short _weight;
        short _field_0x1f6;
        short _gold;
        short _gems;
        short _jewelry;
        char _field_0x1fe;
        bool _isSpellClass1;
        bool _isSpellClass2;
        bool _isSpellClass3;
        bool _itemAtIndex19IsEquipped;
        bool _alive;
        bool _aFlag;
        char _brawn;
        char _knowledge;
        char _judgement;
        char _agility;
        char _vitality;
        char _luck;
        std::array<SpellLevel, 7> _spellList;
        std::string _name;
        short _verifyField2;
        PrestigeValues _prestige;
        std::array<int16_t, 40> _treasureArrayIds;
        short _field_0x304;
        short _field_0x306;
        short _field_0x308;
        short _field_0x30a;
        short _field_0x30c;
        short _field_0x30e;
        short _field_0x310;
        short _field_0x312;
        std::array<short, 42> _field_0x314;
    };
} // end namespace realmz

#endif //REALMZ_TOOLS_CHARACTER_H
