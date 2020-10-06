//
// Created by jwscoggins on 10/4/20.
//

#ifndef REALMZ_TOOLS_CHARACTER_H
#define REALMZ_TOOLS_CHARACTER_H
#include <cstdint>
#include <array>
#include <string>
#include <iostream>
namespace realmz {
    using CharacterDataBuffer = std::array<int16_t, 872/2>;
    class SpecialInfo_CharVersion {
    public:
        SpecialInfo_CharVersion(int16_t first, int16_t second, int16_t third, int16_t fourth, int16_t fifth, int16_t sixth, int16_t seventh) :
        _sneakAttack(first & 0xFF), _causeMajorWound((second >> 8) & 0xFF),
        _detectSecret(third & 0xFF), _acrobaticAct((third >> 8) & 0xFF),
        _detectTrap(fourth & 0xFF), _disableTrap((fourth >> 8) & 0xFF),
        _forceLock((fifth >> 8) & 0xFF), _pickLock((sixth >> 8) & 0xFF),
        _turnUndead((seventh >> 8) & 0xFF) { }


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
        constexpr InventoryItem(int16_t index, uint8_t field2, uint8_t field3, uint16_t flags) noexcept : _idx(index), _f2(field2), _f3(field3), _flags(flags) { }
        [[nodiscard]] constexpr auto getIndex() const noexcept { return _idx; }
        [[nodiscard]] constexpr auto getField2() const noexcept { return _f2; }
        [[nodiscard]] constexpr auto getField3() const noexcept { return _f3; }
        [[nodiscard]] constexpr auto getFlags() const noexcept { return _flags; }
        void print(std::ostream& os) const noexcept;
    private:
        uint16_t _idx;
        uint8_t _f2;
        uint8_t _f3;
        uint16_t _flags;
    };

    using SpellLevel = std::array<bool, 12>;

    class PrestigeValues {
    public:
        constexpr PrestigeValues(int32_t damageTaken, int32_t damageGiven, int32_t hitsGiven, int32_t hitsTaken, int32_t missedAttacks, int32_t dodgedAttacks,
                       int32_t enemiesKilled, int32_t timesDied, int32_t timesUnconscious, int32_t combatSpellsCast, int32_t undeadDestroyed, int32_t undeadTurned,
                       int32_t penaltyPoints) noexcept : _damageTaken(damageTaken), _damageGiven(damageGiven), _hitsGiven(hitsGiven),
                                            _hitsTaken(hitsTaken), _missedAttacks(missedAttacks), _dodgedAttacks(dodgedAttacks),
                                            _enemiesKilled(enemiesKilled), _timesDied(timesDied), _timesUnconscious(timesUnconscious),
                                            _combatSpellsCast(combatSpellsCast), _undeadDestroyed(undeadDestroyed),
                                            _undeadTurned(undeadTurned), _penaltyPoints(penaltyPoints) {}
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
        int32_t _damageTaken;
        int32_t _damageGiven;
        int32_t _hitsGiven;
        int32_t _hitsTaken;
        int32_t _missedAttacks;
        int32_t _dodgedAttacks;
        int32_t _enemiesKilled;
        int32_t _timesDied;
        int32_t _timesUnconscious;
        int32_t _combatSpellsCast;
        int32_t _undeadDestroyed;
        int32_t _undeadTurned;
        int32_t _penaltyPoints;
    };

    class EquippedItems {
    public:
        constexpr EquippedItems(int16_t field0, int16_t field1, int16_t field2, int16_t field3,
                                int16_t ring0, int16_t ring1, int16_t weapon, int16_t shield,
                                int16_t armor, int16_t gauntlets, int16_t cloak, int16_t helm,
                                int16_t luckStone, int16_t boots, int16_t quiver, int16_t belt,
                                int16_t necklace, int16_t field17, int16_t field18, int16_t field19) : _field0(field0),
                                                                                                       _field1(field1),
                                                                                                       _field2(field2),
                                                                                                       _field3(field3),
                                                                                                       _ring0(ring0),
                                                                                                       _ring1(ring1),
                                                                                                       _weapon(weapon),
                                                                                                       _shield(shield),
                                                                                                       _armor(armor),
                                                                                                       _gauntlets(gauntlets),
                                                                                                       _cloak(cloak),
                                                                                                       _helm(helm),
                                                                                                       _luckStone(luckStone),
                                                                                                       _boots(boots),
                                                                                                       _quiver(quiver),
                                                                                                       _belt(belt),
                                                                                                       _necklace(necklace),
                                                                                                       _field17(field17),
                                                                                                       _field18(field18),
                                                                                                       _field19(field19) {}
    public:
        void setField0(int16_t field0) noexcept { _field0 = field0; }
        void setField1(int16_t field1) noexcept { _field1 = field1; }
        void setField2(int16_t field2) noexcept { _field2 = field2; }
        void setField3(int16_t field3) noexcept { _field3 = field3; }
        void setRing0(int16_t ring0) noexcept { _ring0 = ring0; }
        void setRing1(int16_t ring1) noexcept { _ring1 = ring1; }
        void setWeapon(int16_t weapon) noexcept { _weapon = weapon; }
        void setShield(int16_t shield) noexcept { _shield = shield; }
        void setArmor(int16_t armor) noexcept { _armor = armor; }
        void setGauntlets(int16_t gauntlets) noexcept { _gauntlets = gauntlets; }
        void setCloak(int16_t cloak) noexcept { _cloak = cloak; }
        void setHelm(int16_t helm) noexcept { _helm = helm; }
        void setLuckStone(int16_t luckStone) noexcept { _luckStone = luckStone; }
        void setBoots(int16_t boots) noexcept { _boots = boots; }
        void setQuiver(int16_t quiver) noexcept { _quiver = quiver; }
        void setBelt(int16_t belt) noexcept { _belt = belt; }
        void setNecklace(int16_t necklace) noexcept { _necklace = necklace; }
        void setField17(int16_t field17) noexcept { _field17 = field17; }
        void setField18(int16_t field18) noexcept { _field18 = field18; }
        void setField19(int16_t field19) noexcept { _field19 = field19; }
    public:
        [[nodiscard]] constexpr int16_t getField0() const noexcept { return _field0; }
        [[nodiscard]] constexpr int16_t getField1() const noexcept { return _field1; }
        [[nodiscard]] constexpr int16_t getField2() const noexcept { return _field2; }
        [[nodiscard]] constexpr int16_t getField3() const noexcept { return _field3; }
        [[nodiscard]] constexpr int16_t getRing0() const noexcept { return _ring0; }
        [[nodiscard]] constexpr int16_t getRing1() const noexcept { return _ring1; }
        [[nodiscard]] constexpr int16_t getWeapon() const noexcept { return _weapon; }
        [[nodiscard]] constexpr int16_t getShield() const noexcept { return _shield; }
        [[nodiscard]] constexpr int16_t getArmor() const noexcept { return _armor; }
        [[nodiscard]] constexpr int16_t getGauntlets() const noexcept { return _gauntlets; }
        [[nodiscard]] constexpr int16_t getCloak() const noexcept { return _cloak; }
        [[nodiscard]] constexpr int16_t getHelm() const noexcept { return _helm; }
        [[nodiscard]] constexpr int16_t getLuckStone() const noexcept { return _luckStone; }
        [[nodiscard]] constexpr int16_t getBoots() const noexcept { return _boots; }
        [[nodiscard]] constexpr int16_t getQuiver() const noexcept { return _quiver; }
        [[nodiscard]] constexpr int16_t getBelt() const noexcept { return _belt; }
        [[nodiscard]] constexpr int16_t getNecklace() const noexcept { return _necklace; }
        [[nodiscard]] constexpr int16_t getField17() const noexcept { return _field17; }
        [[nodiscard]] constexpr int16_t getField18() const noexcept { return _field18; }
        [[nodiscard]] constexpr int16_t getField19() const noexcept { return _field19; }
        void print(std::ostream& os) const noexcept;
    private:
        int16_t _field0;
        int16_t _field1;
        int16_t _field2;
        int16_t _field3;
        int16_t _ring0;
        int16_t _ring1;
        int16_t _weapon;
        int16_t _shield;
        int16_t _armor;
        int16_t _gauntlets;
        int16_t _cloak;
        int16_t _helm;
        int16_t _luckStone;
        int16_t _boots;
        int16_t _quiver;
        int16_t _belt;
        int16_t _necklace;
        int16_t _field17;
        int16_t _field18;
        int16_t _field19;
    };


    class CharacterConditions {
    public:
        constexpr CharacterConditions(int16_t inRetreat, int16_t helpless, int16_t tangled, int16_t isCursed, int16_t conditionMagicAura,
                                      int16_t supidOrSilenced1, int16_t isSlow, int16_t conditionShieldedFromNormalAttacks,
                                      int16_t conditionShieldedFromProjectiles, int16_t poisoned, int16_t regenerating,
                                      int16_t protectionFromHeatAttacks, int16_t protectionFromColdAttacks, int16_t protectionFromElectricalAttacks,
                                      int16_t protectionFromChemicalAttacks, int16_t protectionFromMentalAttacks,
                                      int16_t protectionFrom1StLevelSpells, int16_t protectionFrom2NdLevelSpells,
                                      int16_t protectionFrom3rdLevelSpells, int16_t protectionFrom4ThLevelSpells,
                                      int16_t protectionFrom5ThLevelSpells) : _inRetreat(inRetreat), _helpless(helpless), _tangled(tangled),
                                                                              _isCursed(isCursed), _conditionMagicAura(conditionMagicAura),
                                                                              _supidOrSilenced1(supidOrSilenced1), _isSlow(isSlow),
                                                                              _conditionShieldedFromNormalAttacks(conditionShieldedFromNormalAttacks),
                                                                              _conditionShieldedFromProjectiles(conditionShieldedFromProjectiles),
                                                                              _poisoned(poisoned), _regenerating(regenerating),
                                                                              _protectionFromHeatAttacks(protectionFromHeatAttacks),
                                                                              _protectionFromColdAttacks(protectionFromColdAttacks),
                                                                              _protectionFromElectricalAttacks(protectionFromElectricalAttacks),
                                                                              _protectionFromChemicalAttacks(protectionFromChemicalAttacks),
                                                                              _protectionFromMentalAttacks(protectionFromMentalAttacks),
                                                                              _protectionFrom1stLevelSpells(protectionFrom1StLevelSpells),
                                                                              _protectionFrom2ndLevelSpells(protectionFrom2NdLevelSpells),
                                                                              _protectionFrom3rdLevelSpells(protectionFrom3rdLevelSpells),
                                                                              _protectionFrom4thLevelSpells(protectionFrom4ThLevelSpells),
                                                                              _protectionFrom5thLevelSpells(protectionFrom5ThLevelSpells) {}
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
        constexpr int16_t getProtectionFrom1stLevelSpells() const noexcept { return _protectionFrom1stLevelSpells; }
        constexpr int16_t getProtectionFrom2ndLevelSpells() const noexcept { return _protectionFrom2ndLevelSpells; }
        constexpr int16_t getProtectionFrom3rdLevelSpells() const noexcept { return _protectionFrom3rdLevelSpells; }
        constexpr int16_t getProtectionFrom4thLevelSpells() const noexcept { return _protectionFrom4thLevelSpells; }
        constexpr int16_t getProtectionFrom5thLevelSpells() const noexcept { return _protectionFrom5thLevelSpells; }
        void print(std::ostream& os) const noexcept;
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
        int16_t _protectionFrom3rdLevelSpells;
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
        void setField0X304(int16_t field0X304) { _field_0x304 = field0X304; }
        void setField0X306(int16_t field0X306) { _field_0x306 = field0X306; }
        void setField0X308(int16_t field0X308) { _field_0x308 = field0X308; }
        void setField0X30A(int16_t field0X30A) { _field_0x30a = field0X30A; }
        void setField0X30C(int16_t field0X30C) { _field_0x30c = field0X30C; }
        void setField0X30E(int16_t field0X30E) { _field_0x30e = field0X30E; }
        void setField0X310(int16_t field0X310) { _field_0x310 = field0X310; }
        void setField0X312(int16_t field0X312) { _field_0x312 = field0X312; }
        void setField0X314(size_t index, int16_t value);
        void setField0X100(size_t index, int16_t value);
        void setTreasureArrayId(size_t index, int16_t value);
    public:
        [[nodiscard]] constexpr int16_t getLuckFromItems() const noexcept { return _luckFromItems; }
        [[nodiscard]] constexpr int16_t getBrawnFromItems() const noexcept { return _brawnFromItems; }
        [[nodiscard]] constexpr int16_t getMagicResistance() const noexcept { return _magicResistance; }
        [[nodiscard]] constexpr int16_t getMovementBonus() const noexcept { return _movementBonus; }
        [[nodiscard]] constexpr int16_t getArmorRating() const noexcept { return _armorRating; }
        [[nodiscard]] constexpr int16_t getDamagePlus() const noexcept { return _damagePlus; }
        [[nodiscard]] constexpr int16_t getRace() const noexcept { return _race; }
        [[nodiscard]] constexpr int16_t getCaste() const noexcept { return _caste; }
        [[nodiscard]] constexpr SupportedSpellClass getSupportedSpellClass() const noexcept { return _supportedSpellClass; }
        [[nodiscard]] constexpr Gender getGender() const noexcept { return _gender; }
        [[nodiscard]] constexpr int16_t getSkillLevel() const noexcept { return _skillLevel; }
        [[nodiscard]] constexpr int16_t getField0X3A() const noexcept { return _field_0x3a; }
        [[nodiscard]] constexpr int16_t getMovementPoints() const noexcept { return _movementPoints; }
        [[nodiscard]] constexpr int16_t getCombatPoints() const noexcept { return _combatPoints; }
        [[nodiscard]] constexpr int16_t getStaminaCurrent() const noexcept { return _staminaCurrent; }
        [[nodiscard]] constexpr int16_t getStaminaTotal() const noexcept { return _staminaTotal; }
        [[nodiscard]] constexpr int16_t getPortraitIndex() const noexcept { return _portraitIndex; }
        [[nodiscard]] constexpr int16_t getIconPictureIndex() const noexcept { return _iconPictureIndex; }
        [[nodiscard]] constexpr int16_t getSpellPointsCurrent() const noexcept { return _spellPointsCurrent; }
        [[nodiscard]] constexpr int16_t getSpellPointsTotal() const noexcept { return _spellPointsTotal; }
        [[nodiscard]] constexpr int16_t getField0X5A() const noexcept { return _field_0x5a; }
        [[nodiscard]] constexpr int16_t getField0X5C() const noexcept { return _field_0x5c; }
        [[nodiscard]] constexpr int16_t getField0X5E() const noexcept { return _field_0x5e; }
        [[nodiscard]] constexpr int16_t getHandToHandMax() const noexcept { return _handToHandMax; }
        [[nodiscard]] constexpr int16_t getStrong() const noexcept { return _strong; }
        [[nodiscard]] constexpr int16_t getProtectionFromFoe() const noexcept { return _protectionFromFoe; }
        [[nodiscard]] constexpr int16_t getSpeed() const noexcept { return _speed; }
        [[nodiscard]] constexpr int16_t getInvisible() const noexcept { return _invisible; }
        [[nodiscard]] constexpr int16_t getIsAnimated() const noexcept { return _isAnimated; }
        [[nodiscard]] constexpr int16_t getStone() const noexcept { return _stone; }
        [[nodiscard]] constexpr int16_t getBlind() const noexcept { return _blind; }
        [[nodiscard]] constexpr int16_t getDiseased() const noexcept { return _diseased; }
        [[nodiscard]] constexpr int16_t getIsConfused() const noexcept { return _isConfused; }
        [[nodiscard]] constexpr int16_t getReflectingSpells() const noexcept { return _reflectingSpells; }
        [[nodiscard]] constexpr int16_t getReflectingAttacks() const noexcept { return _reflectingAttacks; }
        [[nodiscard]] constexpr int16_t getAttackBonus() const noexcept { return _attackBonus; }
        [[nodiscard]] constexpr int16_t getAbsorbEnergy() const noexcept { return _absorbEnergy; }
        [[nodiscard]] constexpr int16_t getAbsorbSpellEnergyFromAttacks() const noexcept { return _absorbSpellEnergyFromAttacks; }
        [[nodiscard]] constexpr int16_t getField0Xa8() const noexcept { return _field_0xa8; }
        [[nodiscard]] constexpr int16_t getHinderedAttack() const noexcept { return _hinderedAttack; }
        [[nodiscard]] constexpr int16_t getHinderedDefense() const noexcept { return _hinderedDefense; }
        [[nodiscard]] constexpr int16_t getDefensiveBonus() const noexcept { return _defensiveBonus; }
        [[nodiscard]] constexpr int16_t getAffectsCastingAbility() const noexcept { return _affectsCastingAbility; }
        [[nodiscard]] constexpr int16_t getVsMagicUsingCreatures() const noexcept { return _vsMagicUsingCreatures; }
        [[nodiscard]] constexpr int16_t getVsUndeadCreatures() const noexcept { return _vsUndeadCreatures; }
        [[nodiscard]] constexpr int16_t getVsDemonicCreatures() const noexcept { return _vsDemonicCreatures; }
        [[nodiscard]] constexpr int16_t getVsReptileCreatures() const noexcept { return _vsReptileCreatures; }
        [[nodiscard]] constexpr int16_t getVsVeryEvilCreatures() const noexcept { return _vsVeryEvilCreatures; }
        [[nodiscard]] constexpr int16_t getVsIntelligentCreatures() const noexcept { return _vsIntelligentCreatures; }
        [[nodiscard]] constexpr int16_t getVsGiantSizedCreatures() const noexcept { return _vsGiantSizedCreatures; }
        [[nodiscard]] constexpr int16_t getVsNonHumanoidCreature() const noexcept { return _vsNonHumanoidCreature; }
        [[nodiscard]] constexpr int16_t getField0Xea() const noexcept { return _field_0xea; }
        [[nodiscard]] constexpr int16_t getField0Xec() const noexcept { return _field_0xec; }
        [[nodiscard]] constexpr int16_t getField0Xee() const noexcept { return _field_0xee; }
        [[nodiscard]] constexpr int16_t getField0Xf0() const noexcept { return _field_0xf0; }
        [[nodiscard]] constexpr int16_t getDamageReductionVsCharm() const noexcept { return _damageReductionVsCharm; }
        [[nodiscard]] constexpr int16_t getDamageReductionVsHeat() const noexcept { return _damageReductionVsHeat; }
        [[nodiscard]] constexpr int16_t getDamageReductionVsCold() const noexcept { return _damageReductionVsCold; }
        [[nodiscard]] constexpr int16_t getDamageReductionVsElectric() const noexcept { return _damageReductionVsElectric; }
        [[nodiscard]] constexpr int16_t getDamageReductionVsChemical() const noexcept { return _damageReductionVsChemical; }
        [[nodiscard]] constexpr int16_t getDamageReductionVsMental() const noexcept { return _damageReductionVsMental; }
        [[nodiscard]] constexpr int16_t getDamageReductionVsMagic() const noexcept { return _damageReductionVsMagic; }
        [[nodiscard]] constexpr int16_t getDamageReductionVsSpecial() const noexcept { return _damageReductionVsSpecial; }
        [[nodiscard]] constexpr int16_t getAgeClass() const noexcept { return _ageClass; }
        [[nodiscard]] constexpr int16_t getVerifyField1() const noexcept { return _verifyField1; }
        [[nodiscard]] constexpr int32_t getDaysOld() const noexcept { return _daysOld; }
        [[nodiscard]] constexpr int32_t getVictoryPoints() const noexcept { return _victoryPoints; }
        [[nodiscard]] constexpr int16_t getWeight() const noexcept { return _weight; }
        [[nodiscard]] constexpr int16_t getField0X1F6() const noexcept { return _field_0x1f6; }
        [[nodiscard]] constexpr int16_t getGold() const noexcept { return _gold; }
        [[nodiscard]] constexpr int16_t getGems() const noexcept { return _gems; }
        [[nodiscard]] constexpr int16_t getJewelry() const noexcept { return _jewelry; }
        [[nodiscard]] constexpr int8_t getField0X1Fe() const noexcept { return _field_0x1fe; }
        [[nodiscard]] constexpr bool isIsSpellClass1() const noexcept { return _isSpellClass1; }
        [[nodiscard]] constexpr bool isIsSpellClass2() const noexcept { return _isSpellClass2; }
        [[nodiscard]] constexpr bool isIsSpellClass3() const noexcept { return _isSpellClass3; }
        [[nodiscard]] constexpr bool isItemAtIndex19IsEquipped() const noexcept { return _itemAtIndex19IsEquipped; }
        [[nodiscard]] constexpr bool isAlive() const noexcept { return _alive; }
        [[nodiscard]] constexpr bool isAFlag() const noexcept { return _aFlag; }
        [[nodiscard]] constexpr char getBrawn() const noexcept { return _brawn; }
        [[nodiscard]] constexpr char getKnowledge() const noexcept { return _knowledge; }
        [[nodiscard]] constexpr char getJudgement() const noexcept { return _judgement; }
        [[nodiscard]] constexpr char getAgility() const noexcept { return _agility; }
        [[nodiscard]] constexpr char getVitality() const noexcept { return _vitality; }
        [[nodiscard]] constexpr char getLuck() const noexcept { return _luck; }
        [[nodiscard]] constexpr int16_t getVerifyField2() const noexcept { return _verifyField2; }
        [[nodiscard]] constexpr int16_t getField0X304() const noexcept { return _field_0x304; }
        [[nodiscard]] constexpr int16_t getField0X306() const noexcept { return _field_0x306; }
        [[nodiscard]] constexpr int16_t getField0X308() const noexcept { return _field_0x308; }
        [[nodiscard]] constexpr int16_t getField0X30A() const noexcept { return _field_0x30a; }
        [[nodiscard]] constexpr int16_t getField0X30C() const noexcept { return _field_0x30c; }
        [[nodiscard]] constexpr int16_t getField0X30E() const noexcept { return _field_0x30e; }
        [[nodiscard]] constexpr int16_t getField0X310() const noexcept { return _field_0x310; }
        [[nodiscard]] constexpr int16_t getField0X312() const noexcept { return _field_0x312; }
        [[nodiscard]] const std::array<int16_t, 8> &getField0X100() const { return _field_0x100; }
        [[nodiscard]] const std::array<SpellLevel, 7> &getSpellList() const { return _spellList; }
        [[nodiscard]] const std::string &getName() const { return _name; }
        [[nodiscard]] const PrestigeValues &getPrestige() const { return _prestige; }
        [[nodiscard]] const std::array<int16_t, 40> &getTreasureArrayIds() const { return _treasureArrayIds; }
        [[nodiscard]] const std::array<int16_t, 42> &getField0X314() const { return _field_0x314; }
        [[nodiscard]] const EquippedItems &getEquippedItems() const { return _equippedItems; }
        [[nodiscard]] const SpecialInfo_CharVersion &getSpecialInfo() const { return _specialInfo; }
        [[nodiscard]] const std::array<InventoryItem, 30> &getItems() const { return _items; }
        [[nodiscard]] const std::array<int16_t, 10> &getAnArray() const { return _anArray; }
        [[nodiscard]] const std::array<int16_t, 7> &getTotalSpellsRemaining() const { return _totalSpellsRemaining; }
        [[nodiscard]] const CharacterConditions &getConditions() const { return _conditions; }
        void print(std::ostream& os) const noexcept;
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
        EquippedItems _equippedItems;
        int16_t _field_0xea;
        int16_t _field_0xec;
        int16_t _field_0xee;
        int16_t _field_0xf0;
        SpecialInfo_CharVersion _specialInfo;
        std::array<int16_t, 8> _field_0x100;
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
        std::array<int16_t, 10> _anArray;
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
std::ostream& operator<<(std::ostream& os, const realmz::Character& c) noexcept;
std::ostream& operator<<(std::ostream& os, const realmz::CharacterConditions& c) noexcept;
std::ostream& operator<<(std::ostream& os, const realmz::InventoryItem& c) noexcept;
std::ostream& operator<<(std::ostream& os, const realmz::EquippedItems& ec) noexcept;

#endif //REALMZ_TOOLS_CHARACTER_H
