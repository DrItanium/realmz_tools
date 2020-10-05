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
        Character(const CharacterDataBuffer& buf);
        void setId(uint16_t id) { _id = id; }
        void setChanceToHit(int16_t chanceToHit) { _chanceToHit = chanceToHit; }
        void setDodgeMissile(int16_t dodgeMissile) { _dodgeMissile = dodgeMissile; }
        void setMissileAdjust(int16_t missileAdjust) { _missileAdjust = missileAdjust; }
        void setBareHandDamageMax(int16_t bareHandDamageMax) { _bareHandDamageMax = bareHandDamageMax; }
        void setAllianceClass(int16_t allianceClass) { _allianceClass = allianceClass; }
        void setAttacksPerRound(int16_t attacksPerRound) { _attacksPerRound = attacksPerRound; }
        void setField0X10(int16_t field0X10) { _field_0x10 = field0X10; }
        void setField0X12(int16_t field0X12) { _field_0x12 = field0X12; }
        void setField0X14(int16_t field0X14) { _field_0x14 = field0X14; }
        void setNumItems(int16_t numItems) { _numItems = numItems; }
        void setField0X18(int16_t field0X18) { _field_0x18 = field0X18; }
        void setField0X1A(int16_t field0X1A) { _field_0x1a = field0X1A; }
        void setField0X1C(int16_t field0X1C) { _field_0x1c = field0X1C; }
        void setOtherAttacksPerRoundModifier(int16_t otherAttacksPerRoundModifier) { _otherAttacksPerRoundModifier = otherAttacksPerRoundModifier; }
        void setVitalityFromItems(int16_t vitalityFromItems) { _vitalityFromItems = vitalityFromItems; }
        void setField0X22(int16_t field0X22) { _field_0x22 = field0X22; }
        void setLuckFromItems(int16_t luckFromItems) { _luckFromItems = luckFromItems; }
        void setBrawnFromItems(int16_t brawnFromItems) { _brawnFromItems = brawnFromItems; }
        void setMagicResistance(int16_t magicResistance) { _magicResistance = magicResistance; }
        void setMovementBonus(int16_t movementBonus) { _movementBonus = movementBonus; }
        void setArmorRating(int16_t armorRating) { _armorRating = armorRating; }
        void setDamagePlus(int16_t damagePlus) { _damagePlus = damagePlus; }
        void setRace(int16_t race) { _race = race; }
        void setCaste(int16_t caste) { _caste = caste; }
        void setSupportedSpellClass(SupportedSpellClass supportedSpellClass) { _supportedSpellClass = supportedSpellClass; }
        void setGender(Gender gender) { _gender = gender; }
        void setSkillLevel(int16_t skillLevel) { _skillLevel = skillLevel; }
        void setField0X3A(int16_t field0X3A) { _field_0x3a = field0X3A; }
        void setMovementPoints(int16_t movementPoints) { _movementPoints = movementPoints; }
        void setCombatPoints(int16_t combatPoints) { _combatPoints = combatPoints; }
        void setTotalSpellsRemaining(size_t index, int16_t value);
        void setStaminaCurrent(int16_t staminaCurrent) { _staminaCurrent = staminaCurrent; }
        void setStaminaTotal(int16_t staminaTotal) { _staminaTotal = staminaTotal; }
        void setPortraitIndex(int16_t portraitIndex) { _portraitIndex = portraitIndex; }
        void setIconPictureIndex(int16_t iconPictureIndex) { _iconPictureIndex = iconPictureIndex; }
        void setSpellPointsCurrent(int16_t spellPointsCurrent) { _spellPointsCurrent = spellPointsCurrent; }
        void setSpellPointsTotal(int16_t spellPointsTotal) { _spellPointsTotal = spellPointsTotal; }
        void setField0X5A(int16_t field0X5A) { _field_0x5a = field0X5A; }
        void setField0X5C(int16_t field0X5C) { _field_0x5c = field0X5C; }
        void setField0X5E(int16_t field0X5E) { _field_0x5e = field0X5E; }
        void setHandToHandMax(int16_t handToHandMax) { _handToHandMax = handToHandMax; }
        void setConditions(const CharacterConditions &conditions) { _conditions = conditions; }
        void setStrong(int16_t strong) { _strong = strong; }
        void setProtectionFromFoe(int16_t protectionFromFoe) { _protectionFromFoe = protectionFromFoe; }
        void setSpeed(int16_t speed) { _speed = speed; }
        void setInvisible(int16_t invisible) { _invisible = invisible; }
        void setIsAnimated(int16_t isAnimated) { _isAnimated = isAnimated; }
        void setStone(int16_t stone) { _stone = stone; }
        void setBlind(int16_t blind) { _blind = blind; }
        void setDiseased(int16_t diseased) { _diseased = diseased; }
        void setIsConfused(int16_t isConfused) { _isConfused = isConfused; }
        void setReflectingSpells(int16_t reflectingSpells) { _reflectingSpells = reflectingSpells; }
        void setReflectingAttacks(int16_t reflectingAttacks) { _reflectingAttacks = reflectingAttacks; }
        void setAttackBonus(int16_t attackBonus) { _attackBonus = attackBonus; }
        void setAbsorbEnergy(int16_t absorbEnergy) { _absorbEnergy = absorbEnergy; }
        void setAbsorbSpellEnergyFromAttacks(int16_t absorbSpellEnergyFromAttacks) { _absorbSpellEnergyFromAttacks = absorbSpellEnergyFromAttacks; }
        void setField0Xa8(int16_t field0Xa8) { _field_0xa8 = field0Xa8; }
        void setHinderedAttack(int16_t hinderedAttack) { _hinderedAttack = hinderedAttack; }
        void setHinderedDefense(int16_t hinderedDefense) { _hinderedDefense = hinderedDefense; }
        void setDefensiveBonus(int16_t defensiveBonus) { _defensiveBonus = defensiveBonus; }
        void setAffectsCastingAbility(int16_t affectsCastingAbility) { _affectsCastingAbility = affectsCastingAbility; }
        void setVsMagicUsingCreatures(int16_t vsMagicUsingCreatures) { _vsMagicUsingCreatures = vsMagicUsingCreatures; }
        void setVsUndeadCreatures(int16_t vsUndeadCreatures) { _vsUndeadCreatures = vsUndeadCreatures; }
        void setVsDemonicCreatures(int16_t vsDemonicCreatures) { _vsDemonicCreatures = vsDemonicCreatures; }
        void setVsReptileCreatures(int16_t vsReptileCreatures) { _vsReptileCreatures = vsReptileCreatures; }
        void setVsVeryEvilCreatures(int16_t vsVeryEvilCreatures) { _vsVeryEvilCreatures = vsVeryEvilCreatures; }
        void setVsIntelligentCreatures(int16_t vsIntelligentCreatures) { _vsIntelligentCreatures = vsIntelligentCreatures; }
        void setVsGiantSizedCreatures(int16_t vsGiantSizedCreatures) { _vsGiantSizedCreatures = vsGiantSizedCreatures; }
        void setVsNonHumanoidCreature(int16_t vsNonHumanoidCreature) { _vsNonHumanoidCreature = vsNonHumanoidCreature; }
        void setEquippedItems(size_t index, int16_t value);
        void setField0Xea(int16_t field0Xea) { _field_0xea = field0Xea; }
        void setField0Xec(int16_t field0Xec) { _field_0xec = field0Xec; }
        void setField0Xee(int16_t field0Xee) { _field_0xee = field0Xee; }
        void setField0Xf0(int16_t field0Xf0) { _field_0xf0 = field0Xf0; }
        SpecialInfo_CharVersion& getSpecialInfo() noexcept { return _specialInfo; }
        void setField0X100(uint8_t field0X100) { _field_0x100 = field0X100; }
        void setField0X101(uint8_t field0X101) { _field_0x101 = field0X101; }
        void setField0X102(uint8_t field0X102) { _field_0x102 = field0X102; }
        void setField0X103(uint8_t field0X103) { _field_0x103 = field0X103; }
        void setField0X104(uint8_t field0X104) { _field_0x104 = field0X104; }
        void setField0X105(uint8_t field0X105) { _field_0x105 = field0X105; }
        void setField0X106(uint8_t field0X106) { _field_0x106 = field0X106; }
        void setField0X107(uint8_t field0X107) { _field_0x107 = field0X107; }
        void setField0X108(uint8_t field0X108) { _field_0x108 = field0X108; }
        void setField0X109(uint8_t field0X109) { _field_0x109 = field0X109; }
        void setField0X10A(uint8_t field0X10A) { _field_0x10a = field0X10A; }
        void setField0X10B(uint8_t field0X10B) { _field_0x10b = field0X10B; }
        void setField0X10C(int16_t field0X10C) { _field_0x10c = field0X10C; }
        void setField0X10E(int16_t field0X10E) { _field_0x10e = field0X10E; }
        void setDamageReductionVsCharm(int16_t damageReductionVsCharm) { _damageReductionVsCharm = damageReductionVsCharm; }
        void setDamageReductionVsHeat(int16_t damageReductionVsHeat) { _damageReductionVsHeat = damageReductionVsHeat; }
        void setDamageReductionVsCold(int16_t damageReductionVsCold) { _damageReductionVsCold = damageReductionVsCold; }
        void setDamageReductionVsElectric(int16_t damageReductionVsElectric) { _damageReductionVsElectric = damageReductionVsElectric; }
        void setDamageReductionVsChemical(int16_t damageReductionVsChemical) { _damageReductionVsChemical = damageReductionVsChemical; }
        void setDamageReductionVsMental(int16_t damageReductionVsMental) { _damageReductionVsMental = damageReductionVsMental; }
        void setDamageReductionVsMagic(int16_t damageReductionVsMagic) { _damageReductionVsMagic = damageReductionVsMagic; }
        void setDamageReductionVsSpecial(int16_t damageReductionVsSpecial) { _damageReductionVsSpecial = damageReductionVsSpecial; }
        void setAgeClass(int16_t ageClass) { _ageClass = ageClass; }
        void setVerifyField1(int16_t verifyField1) { _verifyField1 = verifyField1; }
        void setItem(size_t index, const InventoryItem& item) noexcept;
        void setAnArrayValue(size_t index, int value);
        void setDaysOld(int32_t daysOld) { _daysOld = daysOld; }
        void setVictoryPoints(int32_t victoryPoints) { _victoryPoints = victoryPoints; }
        void setWeight(int16_t weight) { _weight = weight; }
        void setField0X1F6(int16_t field0X1F6) { _field_0x1f6 = field0X1F6; }
        void setGold(int16_t gold) { _gold = gold; }
        void setGems(int16_t gems) { _gems = gems; }
        void setJewelry(int16_t jewelry) { _jewelry = jewelry; }
        void setField0X1Fe(int8_t field0X1Fe) { _field_0x1fe = field0X1Fe; }
        void setIsSpellClass1(bool isSpellClass1) { _isSpellClass1 = isSpellClass1; }
        void setIsSpellClass2(bool isSpellClass2) { _isSpellClass2 = isSpellClass2; }
        void setIsSpellClass3(bool isSpellClass3) { _isSpellClass3 = isSpellClass3; }
        void setItemAtIndex19IsEquipped(bool itemAtIndex19IsEquipped) { _itemAtIndex19IsEquipped = itemAtIndex19IsEquipped; }
        void setAlive(bool alive) { _alive = alive; }
        void setAFlag(bool aFlag) { _aFlag = aFlag; }
        void setBrawn(char brawn) { _brawn = brawn; }
        void setKnowledge(char knowledge) { _knowledge = knowledge; }
        void setJudgement(char judgement) { _judgement = judgement; }
        void setAgility(char agility) { _agility = agility; }
        void setVitality(char vitality) { _vitality = vitality; }
        void setLuck(char luck) { _luck = luck; }
        std::array<SpellLevel, 7>& getSpellList() noexcept { return _spellList; }
        void setName(const std::string &name) { _name = name; }
        void setPrestige(const PrestigeValues &prestige) { _prestige = prestige; }
        void setTreasureArrayIds(const std::array<int16_t, 40> &treasureArrayIds) { _treasureArrayIds = treasureArrayIds; }
        void setField0X304(int16_t field0X304) { _field_0x304 = field0X304; }
        void setField0X306(int16_t field0X306) { _field_0x306 = field0X306; }
        void setField0X308(int16_t field0X308) { _field_0x308 = field0X308; }
        void setField0X30A(int16_t field0X30A) { _field_0x30a = field0X30A; }
        void setField0X30C(int16_t field0X30C) { _field_0x30c = field0X30C; }
        void setField0X30E(int16_t field0X30E) { _field_0x30e = field0X30E; }
        void setField0X310(int16_t field0X310) { _field_0x310 = field0X310; }
        void setField0X312(int16_t field0X312) { _field_0x312 = field0X312; }
        void setField0X314(size_t index, int16_t value);

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
