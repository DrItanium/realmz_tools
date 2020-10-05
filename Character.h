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

    class PrestigeValues {
    public:
        PrestigeValues(const CharacterDataBuffer& buf);
        constexpr auto getDamageTaken() const noexcept { return _damageTaken; }
        constexpr auto getDamageGiven() const noexcept { return _damageGiven; }
        constexpr auto getHitsGiven() const noexcept { return _hitsGiven; }
        constexpr auto getHitsTaken() const noexcept { return _hitsTaken; }
        constexpr auto getMissedAttacks() const noexcept { return _missedAttacks; }
        constexpr auto getDodgedAttacks() const noexcept { return _dodgedAttacks; }
        constexpr auto getEnemiesKilled() const noexcept { return _enemiesKilled; }
        constexpr auto getTimesDied() const noexcept { return _timesDied; }
        constexpr auto getTimesUnconscious() const noexcept { return _timesUnconscious; }
        constexpr auto getCombatSpellsCast() const noexcept { return _combatSpellsCast; }
        constexpr auto getUndeadDestroyed() const noexcept { return _undeadDestroyed; }
        constexpr auto getUndeadTurned() const noexcept { return _undeadTurned; }
        constexpr auto getPenaltyPoints() const noexcept { return _penaltyPoints; }
    private:
        int _damageTaken;
        int _damageGiven;
        int _hitsGiven;
        int _hitsTaken;
        int _missedAttacks;
        int _dodgedAttacks;
        int _enemiesKilled;
        int _timesDied;
        int _timesUnconscious;
        int _combatSpellsCast;
        int _undeadDestroyed;
        int _undeadTurned;
        int _penaltyPoints;
    };




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
    public:

        int16_t getLuckFromItems() const { return _luckFromItems; }
        int16_t getBrawnFromItems() const { return _brawnFromItems; }
        int16_t getMagicResistance() const { return _magicResistance; }
        int16_t getMovementBonus() const { return _movementBonus; }
        int16_t getArmorRating() const { return _armorRating; }
        int16_t getDamagePlus() const { return _damagePlus; }
        int16_t getRace() const { return _race; }
        int16_t getCaste() const { return _caste; }
        SupportedSpellClass getSupportedSpellClass() const { return _supportedSpellClass; }
        Gender getGender() const { return _gender; }
        int16_t getSkillLevel() const { return _skillLevel; }
        int16_t getField0X3A() const { return _field_0x3a; }
        int16_t getMovementPoints() const { return _movementPoints; }
        int16_t getCombatPoints() const { return _combatPoints; }
        const std::array<int16_t, 7> &getTotalSpellsRemaining() const { return _totalSpellsRemaining; }
        int16_t getStaminaCurrent() const { return _staminaCurrent; }
        int16_t getStaminaTotal() const { return _staminaTotal; }
        int16_t getPortraitIndex() const { return _portraitIndex; }
        int16_t getIconPictureIndex() const { return _iconPictureIndex; }
        int16_t getSpellPointsCurrent() const { return _spellPointsCurrent; }
        int16_t getSpellPointsTotal() const { return _spellPointsTotal; }
        int16_t getField0X5A() const { return _field_0x5a; }
        int16_t getField0X5C() const { return _field_0x5c; }
        int16_t getField0X5E() const { return _field_0x5e; }
        int16_t getHandToHandMax() const { return _handToHandMax; }
        const CharacterConditions &getConditions() const { return _conditions; }
        int16_t getStrong() const { return _strong; }
        int16_t getProtectionFromFoe() const { return _protectionFromFoe; }
        int16_t getSpeed() const { return _speed; }
        int16_t getInvisible() const { return _invisible; }
        int16_t getIsAnimated() const { return _isAnimated; }
        int16_t getStone() const { return _stone; }
        int16_t getBlind() const { return _blind; }
        int16_t getDiseased() const { return _diseased; }
        int16_t getIsConfused() const { return _isConfused; }
        int16_t getReflectingSpells() const { return _reflectingSpells; }
        int16_t getReflectingAttacks() const { return _reflectingAttacks; }
        int16_t getAttackBonus() const { return _attackBonus; }
        int16_t getAbsorbEnergy() const { return _absorbEnergy; }
        int16_t getAbsorbSpellEnergyFromAttacks() const { return _absorbSpellEnergyFromAttacks; }
        int16_t getField0Xa8() const { return _field_0xa8; }
        int16_t getHinderedAttack() const { return _hinderedAttack; }
        int16_t getHinderedDefense() const { return _hinderedDefense; }
        int16_t getDefensiveBonus() const { return _defensiveBonus; }
        int16_t getAffectsCastingAbility() const { return _affectsCastingAbility; }
        int16_t getVsMagicUsingCreatures() const { return _vsMagicUsingCreatures; }
        int16_t getVsUndeadCreatures() const { return _vsUndeadCreatures; }
        int16_t getVsDemonicCreatures() const { return _vsDemonicCreatures; }
        int16_t getVsReptileCreatures() const { return _vsReptileCreatures; }
        int16_t getVsVeryEvilCreatures() const { return _vsVeryEvilCreatures; }
        int16_t getVsIntelligentCreatures() const { return _vsIntelligentCreatures; }
        int16_t getVsGiantSizedCreatures() const { return _vsGiantSizedCreatures; }
        int16_t getVsNonHumanoidCreature() const { return _vsNonHumanoidCreature; }
        const std::array<int16_t, 20> &getEquippedItems() const { return _equippedItems; }
        int16_t getField0Xea() const { return _field_0xea; }
        int16_t getField0Xec() const { return _field_0xec; }
        int16_t getField0Xee() const { return _field_0xee; }
        int16_t getField0Xf0() const { return _field_0xf0; }
        const SpecialInfo_CharVersion &getSpecialInfo() const { return _specialInfo; }
        uint8_t getField0X100() const { return _field_0x100; }
        uint8_t getField0X101() const { return _field_0x101; }
        uint8_t getField0X102() const { return _field_0x102; }
        uint8_t getField0X103() const { return _field_0x103; }
        uint8_t getField0X104() const { return _field_0x104; }
        uint8_t getField0X105() const { return _field_0x105; }
        uint8_t getField0X106() const { return _field_0x106; }
        uint8_t getField0X107() const { return _field_0x107; }
        uint8_t getField0X108() const { return _field_0x108; }
        uint8_t getField0X109() const { return _field_0x109; }
        uint8_t getField0X10A() const { return _field_0x10a; }
        uint8_t getField0X10B() const { return _field_0x10b; }
        int16_t getField0X10C() const { return _field_0x10c; }
        int16_t getField0X10E() const { return _field_0x10e; }
        int16_t getDamageReductionVsCharm() const { return _damageReductionVsCharm; }
        int16_t getDamageReductionVsHeat() const { return _damageReductionVsHeat; }
        int16_t getDamageReductionVsCold() const { return _damageReductionVsCold; }
        int16_t getDamageReductionVsElectric() const { return _damageReductionVsElectric; }
        int16_t getDamageReductionVsChemical() const { return _damageReductionVsChemical; }
        int16_t getDamageReductionVsMental() const { return _damageReductionVsMental; }
        int16_t getDamageReductionVsMagic() const { return _damageReductionVsMagic; }
        int16_t getDamageReductionVsSpecial() const { return _damageReductionVsSpecial; }
        int16_t getAgeClass() const { return _ageClass; }
        int16_t getVerifyField1() const { return _verifyField1; }
        const std::array<InventoryItem, 30> &getItems() const { return _items; }
        const std::array<int, 5> &getAnArray() const { return _anArray; }
        int32_t getDaysOld() const { return _daysOld; }
        int32_t getVictoryPoints() const { return _victoryPoints; }
        int16_t getWeight() const { return _weight; }
        int16_t getField0X1F6() const { return _field_0x1f6; }
        int16_t getGold() const { return _gold; }
        int16_t getGems() const { return _gems; }
        int16_t getJewelry() const { return _jewelry; }
        int8_t getField0X1Fe() const { return _field_0x1fe; }
        bool isIsSpellClass1() const { return _isSpellClass1; }
        bool isIsSpellClass2() const { return _isSpellClass2; }
        bool isIsSpellClass3() const { return _isSpellClass3; }
        bool isItemAtIndex19IsEquipped() const { return _itemAtIndex19IsEquipped; }
        bool isAlive() const { return _alive; }
        bool isAFlag() const { return _aFlag; }
        char getBrawn() const { return _brawn; }
        char getKnowledge() const { return _knowledge; }
        char getJudgement() const { return _judgement; }
        char getAgility() const { return _agility; }
        char getVitality() const { return _vitality; }
        char getLuck() const { return _luck; }
        const std::array<SpellLevel, 7> &getSpellList() const { return _spellList; }
        const std::string &getName() const { return _name; }
        int16_t getVerifyField2() const { return _verifyField2; }
        const PrestigeValues &getPrestige() const { return _prestige; }
        const std::array<int16_t, 40> &getTreasureArrayIds() const { return _treasureArrayIds; }
        int16_t getField0X304() const { return _field_0x304; }
        int16_t getField0X306() const { return _field_0x306; }
        int16_t getField0X308() const { return _field_0x308; }
        int16_t getField0X30A() const { return _field_0x30a; }
        int16_t getField0X30C() const { return _field_0x30c; }
        int16_t getField0X30E() const { return _field_0x30e; }
        int16_t getField0X310() const { return _field_0x310; }
        int16_t getField0X312() const { return _field_0x312; }
        const std::array<int16_t, 42> &getField0X314() const { return _field_0x314; }
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
        int16_t _staminaCurrent;
        int16_t _staminaTotal;
        int16_t _portraitIndex;
        int16_t _iconPictureIndex;
        int16_t _spellPointsCurrent;
        int16_t _spellPointsTotal;
        int16_t _field_0x5a;
        int16_t _field_0x5c;
        int16_t _field_0x5e;
        int16_t _handToHandMax;
        CharacterConditions _conditions;
        int16_t _strong;
        int16_t _protectionFromFoe;
        int16_t _speed;
        int16_t _invisible;
        int16_t _isAnimated;
        int16_t _stone;
        int16_t _blind;
        int16_t _diseased;
        int16_t _isConfused;
        int16_t _reflectingSpells;
        int16_t _reflectingAttacks;
        int16_t _attackBonus;
        int16_t _absorbEnergy;
        int16_t _absorbSpellEnergyFromAttacks;
        int16_t _field_0xa8;
        int16_t _hinderedAttack;
        int16_t _hinderedDefense;
        int16_t _defensiveBonus;
        int16_t _affectsCastingAbility;
        int16_t _vsMagicUsingCreatures;
        int16_t _vsUndeadCreatures;
        int16_t _vsDemonicCreatures;
        int16_t _vsReptileCreatures;
        int16_t _vsVeryEvilCreatures;
        int16_t _vsIntelligentCreatures;
        int16_t _vsGiantSizedCreatures;
        int16_t _vsNonHumanoidCreature;
        std::array<int16_t, 20> _equippedItems;
        int16_t _field_0xea;
        int16_t _field_0xec;
        int16_t _field_0xee;
        int16_t _field_0xf0;
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
        int16_t _field_0x10c;
        int16_t _field_0x10e;
        int16_t _damageReductionVsCharm;
        int16_t _damageReductionVsHeat;
        int16_t _damageReductionVsCold;
        int16_t _damageReductionVsElectric;
        int16_t _damageReductionVsChemical;
        int16_t _damageReductionVsMental;
        int16_t _damageReductionVsMagic;
        int16_t _damageReductionVsSpecial;
        int16_t _ageClass;
        int16_t _verifyField1;
        std::array<InventoryItem, 30> _items;
        std::array<int, 5> _anArray;
        int32_t _daysOld;
        int32_t _victoryPoints;
        int16_t _weight;
        int16_t _field_0x1f6;
        int16_t _gold;
        int16_t _gems;
        int16_t _jewelry;
        int8_t _field_0x1fe;
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
        int16_t _verifyField2;
        PrestigeValues _prestige;
        std::array<int16_t, 40> _treasureArrayIds;
        int16_t _field_0x304;
        int16_t _field_0x306;
        int16_t _field_0x308;
        int16_t _field_0x30a;
        int16_t _field_0x30c;
        int16_t _field_0x30e;
        int16_t _field_0x310;
        int16_t _field_0x312;
        std::array<int16_t, 42> _field_0x314;
    };
} // end namespace realmz

#endif //REALMZ_TOOLS_CHARACTER_H
