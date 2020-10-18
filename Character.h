//
// Created by jwscoggins on 10/4/20.
//

#ifndef REALMZ_TOOLS_CHARACTER_H
#define REALMZ_TOOLS_CHARACTER_H
#include <cstdint>
#include <array>
#include <string>
#include <iostream>
#include "Caste.h"
#include "RaceData.h"
#include "BinaryManipulation.h"
namespace realmz {
    using CharacterDataBuffer = std::array<int16_t, 872/2>;
    class SpecialInfo_CharVersion {
    public:
        constexpr SpecialInfo_CharVersion(int8_t sneakAttack, int8_t causeMajorWound, int8_t detectSecret, int8_t acrobaticAct, int8_t detectTrap,
                                          int8_t disableTrap, int8_t forceLock, int8_t pickLock, int8_t turnUndead) : _sneakAttack(sneakAttack),
                                                                                                                      _causeMajorWound(
                                                                                                                              causeMajorWound),
                                                                                                                      _detectSecret(detectSecret),
                                                                                                                      _acrobaticAct(acrobaticAct),
                                                                                                                      _detectTrap(detectTrap),
                                                                                                                      _disableTrap(disableTrap),
                                                                                                                      _forceLock(forceLock),
                                                                                                                      _pickLock(pickLock),
                                                                                                                      _turnUndead(turnUndead) {}
        constexpr SpecialInfo_CharVersion(int16_t first, int16_t second, int16_t third, int16_t fourth, int16_t fifth, int16_t sixth, int16_t seventh) :
                SpecialInfo_CharVersion(first & 0xFF,
                                        (second>>8) & 0xFF,
                                        third & 0xFF, (third >> 8) & 0xFF,
                                        fourth & 0xFF, (fourth >> 8) & 0xFF,
                                        (fifth>>8) & 0xFF,
                                        (sixth>>8) & 0xFF,
                                        (seventh>>8) & 0xFF) { }
        SpecialInfo_CharVersion() = default;

        void setSneakAttack(int8_t sneakAttack) noexcept { _sneakAttack = sneakAttack; }
        void setCauseMajorWound(int8_t causeMajorWound) noexcept { _causeMajorWound = causeMajorWound; }
        void setDetectSecret(int8_t detectSecret) noexcept { _detectSecret = detectSecret; }
        void setAcrobaticAct(int8_t acrobaticAct) noexcept { _acrobaticAct = acrobaticAct; }
        void setDetectTrap(int8_t detectTrap) noexcept { _detectTrap = detectTrap; }
        void setDisableTrap(int8_t disableTrap) noexcept { _disableTrap = disableTrap; }
        void setForceLock(int8_t forceLock) noexcept { _forceLock = forceLock; }
        void setPickLock(int8_t pickLock) noexcept { _pickLock = pickLock; }
        void setTurnUndead(int8_t turnUndead) noexcept { _turnUndead = turnUndead; }
        constexpr int8_t getSneakAttack() const noexcept { return _sneakAttack; }
        constexpr int8_t getCauseMajorWound() const noexcept { return _causeMajorWound; }
        constexpr int8_t getDetectSecret() const noexcept { return _detectSecret; }
        constexpr int8_t getAcrobaticAct() const noexcept { return _acrobaticAct; }
        constexpr int8_t getDetectTrap() const noexcept { return _detectTrap; }
        constexpr int8_t getDisableTrap() const noexcept { return _disableTrap; }
        constexpr int8_t getForceLock() const noexcept { return _forceLock; }
        constexpr int8_t getPickLock() const noexcept { return _pickLock; }
        constexpr int8_t getTurnUndead() const noexcept { return _turnUndead; }
        void print(std::ostream& os) const noexcept;
    private:
        int8_t _sneakAttack = 0;
        int8_t _causeMajorWound = 0;
        int8_t _detectSecret = 0;
        int8_t _acrobaticAct = 0;
        int8_t _detectTrap = 0;
        int8_t _disableTrap = 0;
        int8_t _forceLock = 0;
        int8_t _pickLock = 0;
        int8_t _turnUndead = 0;
    };
    class InventoryItem {
    public:
        constexpr InventoryItem(int16_t index, bool equipped, uint8_t field3, uint16_t flags) noexcept : _idx(index), _equipped(equipped), _f3(field3), _flags(flags) { }
        InventoryItem() = default;
        void setIndex(uint16_t idx) noexcept { _idx = idx; }
        void setEquipped(bool value) noexcept { _equipped = value; }
        void setF3(uint8_t value) noexcept { _f3 = value; }
        void setFlags(uint16_t value) noexcept { _flags = value; }
        [[nodiscard]] constexpr auto getIndex() const noexcept { return _idx; }
        [[nodiscard]] constexpr auto isEquipped() const noexcept { return _equipped; }
        [[nodiscard]] constexpr auto getField3() const noexcept { return _f3; }
        [[nodiscard]] constexpr auto getFlags() const noexcept { return _flags; }
        void print(std::ostream& os) const noexcept;
    private:
        uint16_t _idx = 0;
        bool _equipped = false;
        uint8_t _f3 = 0;
        uint16_t _flags = 0;
    };

    using SpellLevel = std::array<bool, 12>;

    class PrestigeValues {
    public:
        PrestigeValues() = default;
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
        void print(std::ostream& os) const noexcept;

        constexpr auto getCurrentPrestige() const noexcept {
            auto damagePrestige = (_damageGiven - _damageTaken) / 20;
            auto combatSpellsCastTotal = _combatSpellsCast * -3;
            auto hitsTakenTotal = _hitsTaken * -2;
            auto missedAttacksTotal = _missedAttacks * -2;
            auto timesUnconsciousTotal = _timesUnconscious * -35;
            auto timesKilledTotal = _timesDied * -75;
            auto enemiesKilledTotal = _enemiesKilled * 3;
            auto hitsGivenTotal = _hitsGiven;
            auto dodgedAttacksTotal = _dodgedAttacks;
            auto undeadDestroyedTotal = _undeadDestroyed * 2;
            auto undeadTurnedTotal = _undeadTurned * 3;
            return damagePrestige + combatSpellsCastTotal + hitsTakenTotal + missedAttacksTotal +
            timesUnconsciousTotal + timesKilledTotal + enemiesKilledTotal + hitsGivenTotal +
            dodgedAttacksTotal + undeadDestroyedTotal +
            undeadTurnedTotal + (-_penaltyPoints);
        }
    private:
        int32_t _damageTaken = 0;
        int32_t _damageGiven = 0;
        int32_t _hitsGiven = 0;
        int32_t _hitsTaken = 0;
        int32_t _missedAttacks = 0;
        int32_t _dodgedAttacks = 0;
        int32_t _enemiesKilled = 0;
        int32_t _timesDied = 0;
        int32_t _timesUnconscious = 0;
        int32_t _combatSpellsCast = 0;
        int32_t _undeadDestroyed = 0;
        int32_t _undeadTurned = 0;
        int32_t _penaltyPoints = 0;
    };

    class EquippedItems {
    public:
        EquippedItems() = default;
        constexpr EquippedItems(int16_t field0, int16_t field1, int16_t field2, int16_t field3,
                                int16_t ring0, int16_t ring1, int16_t weapon, int16_t shield,
                                int16_t armor, int16_t gauntlets, int16_t cloak, int16_t helm,
                                int16_t luckStone, int16_t boots, int16_t quiver, int16_t belt,
                                int16_t necklace, int16_t scrollCase, int16_t field18, int16_t bow,
                                int16_t unused5, int16_t unused6, int16_t unused7, int16_t unused8) : _unused0(field0),
                                                                                                   _unused1(field1),
                                                                                                   _unused2(field2),
                                                                                                   _unused3(field3),
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
                                                                                                   _scrollCase(scrollCase),
                                                                                                   _unused4(field18),
                                                                                                   _bow(bow),
                                                                                                   _unused5(unused5),
                                                                                                   _unused6(unused6),
                                                                                                   _unused7(unused7),
                                                                                                   _unused8(unused8) { }
    public:
        void setField0(int16_t field0) noexcept { _unused0 = field0; }
        void setField1(int16_t field1) noexcept { _unused1 = field1; }
        void setField2(int16_t field2) noexcept { _unused2 = field2; }
        void setField3(int16_t field3) noexcept { _unused3 = field3; }
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
        void setScrollCase(int16_t field17) noexcept { _scrollCase = field17; }
        void setField18(int16_t field18) noexcept { _unused4 = field18; }
        void setBow(int16_t value) noexcept { _bow = value; }
    public:
        [[nodiscard]] constexpr int16_t getField0() const noexcept { return _unused0; }
        [[nodiscard]] constexpr int16_t getField1() const noexcept { return _unused1; }
        [[nodiscard]] constexpr int16_t getField2() const noexcept { return _unused2; }
        [[nodiscard]] constexpr int16_t getField3() const noexcept { return _unused3; }
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
        [[nodiscard]] constexpr int16_t getScrollCase() const noexcept { return _scrollCase; }
        [[nodiscard]] constexpr int16_t getField18() const noexcept { return _unused4; }
        [[nodiscard]] constexpr int16_t getBow() const noexcept { return _bow; }
        void print(std::ostream& os) const noexcept;
    private:
        int16_t _unused0 = 0;
        int16_t _unused1 = 0;
        int16_t _unused2 = 0;
        int16_t _unused3 = 0;
        int16_t _ring0 = 0;
        int16_t _ring1 = 0;
        int16_t _weapon = 0;
        int16_t _shield = 0;
        int16_t _armor = 0;
        int16_t _gauntlets = 0;
        int16_t _cloak = 0;
        int16_t _helm = 0;
        int16_t _luckStone = 0;
        int16_t _boots = 0;
        int16_t _quiver = 0;
        int16_t _belt = 0;
        int16_t _necklace = 0;
        int16_t _scrollCase = 0;
        int16_t _unused4 = 0;
        int16_t _bow = 0;
        int16_t _unused5 = 0;
        int16_t _unused6 = 0;
        int16_t _unused7 = 0;
        int16_t _unused8 = 0;
    };


    class CharacterConditions {
    public:
        CharacterConditions() = default;
        constexpr CharacterConditions(int16_t inRetreat, int16_t helpless, int16_t tangled, int16_t isCursed, int16_t conditionMagicAura,
                            int16_t supidOrSilenced1, int16_t isSlow, int16_t conditionShieldedFromNormalAttacks,
                            int16_t conditionShieldedFromProjectiles, int16_t poisoned, int16_t regenerating,
                            int16_t protectionFromHeatAttacks, int16_t protectionFromColdAttacks, int16_t protectionFromElectricalAttacks,
                            int16_t protectionFromChemicalAttacks, int16_t protectionFromMentalAttacks,
                            int16_t protectionFrom1StLevelSpells, int16_t protectionFrom2NdLevelSpells,
                            int16_t protectionFrom3RdLevelSpells, int16_t protectionFrom4ThLevelSpells,
                            int16_t protectionFrom5ThLevelSpells, int16_t strong, int16_t protectionFromFoe, int16_t speed,
                            int16_t invisible, int16_t isAnimated, int16_t stone, int16_t blind, int16_t diseased, int16_t isConfused,
                            int16_t reflectingSpells, int16_t reflectingAttacks, int16_t attackBonus, int16_t absorbEnergy,
                            int16_t absorbSpellEnergyFromAttacks, int16_t field0Xa8, int16_t hinderedAttack, int16_t hinderedDefense,
                            int16_t defensiveBonus, int16_t affectsCastingAbility) : _inRetreat(inRetreat), _helpless(helpless),
                                                                                     _tangled(tangled), _isCursed(isCursed),
                                                                                     _conditionMagicAura(conditionMagicAura),
                                                                                     _stupid(supidOrSilenced1), _isSlow(isSlow),
                                                                                     _conditionShieldedFromNormalAttacks(
                                                                                             conditionShieldedFromNormalAttacks),
                                                                                     _conditionShieldedFromProjectiles(
                                                                                             conditionShieldedFromProjectiles),
                                                                                     _poisoned(poisoned), _regenerating(regenerating),
                                                                                     _protectionFromHeatAttacks(protectionFromHeatAttacks),
                                                                                     _protectionFromColdAttacks(protectionFromColdAttacks),
                                                                                     _protectionFromElectricalAttacks(
                                                                                             protectionFromElectricalAttacks),
                                                                                     _protectionFromChemicalAttacks(
                                                                                             protectionFromChemicalAttacks),
                                                                                     _protectionFromMentalAttacks(
                                                                                             protectionFromMentalAttacks),
                                                                                     _protectionFrom1stLevelSpells(
                                                                                             protectionFrom1StLevelSpells),
                                                                                     _protectionFrom2ndLevelSpells(
                                                                                             protectionFrom2NdLevelSpells),
                                                                                     _protectionFrom3rdLevelSpells(
                                                                                             protectionFrom3RdLevelSpells),
                                                                                     _protectionFrom4thLevelSpells(
                                                                                             protectionFrom4ThLevelSpells),
                                                                                     _protectionFrom5thLevelSpells(
                                                                                             protectionFrom5ThLevelSpells), _strong(strong),
                                                                                     _protectionFromFoe(protectionFromFoe), _speedy(speed),
                                                                                     _invisible(invisible), _isAnimated(isAnimated),
                                                                                     _stone(stone), _blind(blind), _diseased(diseased),
                                                                                     _confused(isConfused),
                                                                                     _reflectingSpells(reflectingSpells),
                                                                                     _reflectingAttacks(reflectingAttacks),
                                                                                     _bonusDamage(attackBonus), _absorbEnergy(absorbEnergy),
                                                                                     _energyDraining(
                                                                                             absorbSpellEnergyFromAttacks),
                                                                                     _absorbSpellEnergyFromAttacks(field0Xa8),
                                                                                     _hinderedAttack(hinderedAttack),
                                                                                     _hinderedDefense(hinderedDefense),
                                                                                     _defensiveBonus(defensiveBonus),
                                                                                     _silenced(affectsCastingAbility) {}
        [[nodiscard]] constexpr int16_t getInRetreat() const noexcept { return _inRetreat; }
        [[nodiscard]] constexpr int16_t getHelpless() const noexcept { return _helpless; }
        [[nodiscard]] constexpr int16_t getTangled() const noexcept { return _tangled; }
        [[nodiscard]] constexpr int16_t getIsCursed() const noexcept { return _isCursed; }
        [[nodiscard]] constexpr int16_t getConditionMagicAura() const noexcept { return _conditionMagicAura; }
        [[nodiscard]] constexpr int16_t getSupidOrSilenced1() const noexcept { return _stupid; }
        [[nodiscard]] constexpr int16_t getIsSlow() const noexcept { return _isSlow; }
        [[nodiscard]] constexpr int16_t getConditionShieldedFromNormalAttacks() const noexcept { return _conditionShieldedFromNormalAttacks; }
        [[nodiscard]] constexpr int16_t getConditionShieldedFromProjectiles() const noexcept { return _conditionShieldedFromProjectiles; }
        [[nodiscard]] constexpr int16_t getPoisoned() const noexcept { return _poisoned; }
        [[nodiscard]] constexpr int16_t getRegenerating() const noexcept { return _regenerating; }
        [[nodiscard]] constexpr int16_t getProtectionFromHeatAttacks() const noexcept { return _protectionFromHeatAttacks; }
        [[nodiscard]] constexpr int16_t getProtectionFromColdAttacks() const noexcept { return _protectionFromColdAttacks; }
        [[nodiscard]] constexpr int16_t getProtectionFromElectricalAttacks() const noexcept { return _protectionFromElectricalAttacks; }
        [[nodiscard]] constexpr int16_t getProtectionFromChemicalAttacks() const noexcept { return _protectionFromChemicalAttacks; }
        [[nodiscard]] constexpr int16_t getProtectionFromMentalAttacks() const noexcept { return _protectionFromMentalAttacks; }
        [[nodiscard]] constexpr int16_t getProtectionFrom1stLevelSpells() const noexcept { return _protectionFrom1stLevelSpells; }
        [[nodiscard]] constexpr int16_t getProtectionFrom2ndLevelSpells() const noexcept { return _protectionFrom2ndLevelSpells; }
        [[nodiscard]] constexpr int16_t getProtectionFrom3rdLevelSpells() const noexcept { return _protectionFrom3rdLevelSpells; }
        [[nodiscard]] constexpr int16_t getProtectionFrom4thLevelSpells() const noexcept { return _protectionFrom4thLevelSpells; }
        [[nodiscard]] constexpr int16_t getProtectionFrom5thLevelSpells() const noexcept { return _protectionFrom5thLevelSpells; }
        void print(std::ostream& os) const noexcept;
    private:
        int16_t _inRetreat = 0;
        int16_t _helpless = 0;
        int16_t _tangled = 0;
        int16_t _isCursed = 0;
        int16_t _conditionMagicAura = 0;
        int16_t _stupid = 0;
        int16_t _isSlow = 0;
        int16_t _conditionShieldedFromNormalAttacks = 0;
        int16_t _conditionShieldedFromProjectiles = 0;
        int16_t _poisoned = 0;
        int16_t _regenerating = 0;
        int16_t _protectionFromHeatAttacks = 0;
        int16_t _protectionFromColdAttacks = 0;
        int16_t _protectionFromElectricalAttacks = 0;
        int16_t _protectionFromChemicalAttacks = 0;
        int16_t _protectionFromMentalAttacks = 0;
        int16_t _protectionFrom1stLevelSpells = 0;
        int16_t _protectionFrom2ndLevelSpells = 0;
        int16_t _protectionFrom3rdLevelSpells = 0;
        int16_t _protectionFrom4thLevelSpells = 0;
        int16_t _protectionFrom5thLevelSpells = 0;
        int16_t _strong = 0;
        int16_t _protectionFromFoe = 0;
        int16_t _speedy = 0;
        int16_t _invisible = 0;
        int16_t _isAnimated = 0;
        int16_t _stone = 0;
        int16_t _blind = 0;
        int16_t _diseased = 0;
        int16_t _confused = 0;
        int16_t _reflectingSpells = 0;
        int16_t _reflectingAttacks = 0;
        int16_t _bonusDamage = 0;
        int16_t _absorbEnergy = 0;
        int16_t _energyDraining = 0;
        int16_t _absorbSpellEnergyFromAttacks = 0;
        int16_t _hinderedAttack = 0;
        int16_t _hinderedDefense = 0;
        int16_t _defensiveBonus = 0;
        int16_t _silenced = 0;
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
    using OutOfPair = std::tuple<int16_t, int16_t>;
    class Character {
    public:
        Character(const CharacterDataBuffer& buf);
        Character() = default;
        void setId(uint16_t id) noexcept { _id = id; }
        void setChanceToHit(int16_t chanceToHit) noexcept { _chanceToHit = chanceToHit; }
        void setDodgeMissile(int16_t dodgeMissile) noexcept { _dodgeMissile = dodgeMissile; }
        void setMissileAdjust(int16_t missileAdjust) noexcept { _missileAdjust = missileAdjust; }
        void setBareHandDamageMax(int16_t bareHandDamageMax) noexcept { _bareHandDamageMax = bareHandDamageMax; }
        void setAllianceClass(int16_t allianceClass) noexcept { _allianceClass = allianceClass; }
        void setAttacksPerRound(int16_t attacksPerRound) noexcept { _attacksPerRound = attacksPerRound; }
        void setTookNoDamageThisRound(int16_t field0X10) noexcept { _tookNoDamageThisRound = field0X10; }
        void setField0X12(int16_t field0X12) noexcept { _field_0x12 = field0X12; }
        void setField0X14(int16_t field0X14) noexcept { _field_0x14 = field0X14; }
        void setNumItems(int16_t numItems) noexcept { _numItems = numItems; }
        void setField0X18(int16_t field0X18) noexcept { _handToHandSoundIndex = field0X18; }
        void setField0X1A(int16_t field0X1A) noexcept { _unusedField1 = field0X1A; }
        void setField0X1C(int16_t field0X1C) noexcept { _combatBodyIconBase = field0X1C; }
        void setOtherAttacksPerRoundModifier(int16_t otherAttacksPerRoundModifier) noexcept { _otherAttacksPerRoundModifier = otherAttacksPerRoundModifier; }
        void setVitalityFromItems(int16_t vitalityFromItems) noexcept { _vitalityFromItems = vitalityFromItems; }
        void setField0X22(int16_t field0X22) noexcept { _battleOrder = field0X22; }
        void setLuckFromItems(int16_t luckFromItems) noexcept { _luckFromItems = luckFromItems; }
        void setBrawnFromItems(int16_t brawnFromItems) noexcept { _brawnFromItems = brawnFromItems; }
        void setMagicResistance(int16_t magicResistance) noexcept { _magicResistance = magicResistance; }
        void setMovementBonus(int16_t movementBonus) noexcept { _movementBonus = movementBonus; }
        void setArmorRating(int16_t armorRating) noexcept { _armorRating = armorRating; }
        void setDamagePlus(int16_t damagePlus) noexcept { _damagePlus = damagePlus; }
        void setRace(RaceKind race) noexcept { _race = race; }
        void setCaste(CasteKind caste) noexcept { _caste = caste; }
        void setSupportedSpellClass(SupportedSpellClass supportedSpellClass) noexcept { _supportedSpellClass = supportedSpellClass; }
        void setGender(Gender gender) noexcept { _gender = gender; }
        void setSkillLevel(int16_t skillLevel) noexcept { _skillLevel = skillLevel; }
        void setField0X3A(int16_t field0X3A) noexcept { _remainingMovementPoints = field0X3A; }
        void setMovementPoints(int16_t movementPoints) noexcept { _movementPoints = movementPoints; }
        void setCombatPoints(int16_t combatPoints) noexcept { _combatPoints = combatPoints; }
        void setTotalSpellsRemaining(size_t index, int16_t value) noexcept;
        void setStaminaCurrent(int16_t staminaCurrent) noexcept { _staminaCurrent = staminaCurrent; }
        void setStaminaTotal(int16_t staminaTotal) noexcept { _staminaTotal = staminaTotal; }
        void setPortraitIndex(int16_t portraitIndex) noexcept { _portraitIndex = portraitIndex; }
        void setIconPictureIndex(int16_t iconPictureIndex) noexcept { _iconPictureIndex = iconPictureIndex; }
        void setSpellPointsCurrent(int16_t spellPointsCurrent) noexcept { _spellPointsCurrent = spellPointsCurrent; }
        void setSpellPointsTotal(int16_t spellPointsTotal) noexcept { _spellPointsTotal = spellPointsTotal; }
        void setField0X5A(int16_t field0X5A) noexcept { _handsUsed = field0X5A; }
        void setField0X5C(int16_t field0X5C) noexcept { _meleeWeaponEquipped_Probably = field0X5C; }
        void setField0X5E(int16_t field0X5E) noexcept { _rangedWeaponEquipped_Probably = field0X5E; }
        void setHandToHandMax(int16_t handToHandMax) noexcept { _handToHandMax = handToHandMax; }
        void setConditions(const CharacterConditions &conditions) noexcept { _conditions = conditions; }
        void setVsMagicUsingCreatures(int16_t vsMagicUsingCreatures) noexcept { _vsMagicUsingCreatures = vsMagicUsingCreatures; }
        void setVsUndeadCreatures(int16_t vsUndeadCreatures) noexcept { _vsUndeadCreatures = vsUndeadCreatures; }
        void setVsDemonicCreatures(int16_t vsDemonicCreatures) noexcept { _vsDemonicCreatures = vsDemonicCreatures; }
        void setVsReptileCreatures(int16_t vsReptileCreatures) noexcept { _vsReptileCreatures = vsReptileCreatures; }
        void setVsVeryEvilCreatures(int16_t vsVeryEvilCreatures) noexcept { _vsVeryEvilCreatures = vsVeryEvilCreatures; }
        void setVsIntelligentCreatures(int16_t vsIntelligentCreatures) noexcept { _vsIntelligentCreatures = vsIntelligentCreatures; }
        void setVsGiantSizedCreatures(int16_t vsGiantSizedCreatures) noexcept { _vsGiantSizedCreatures = vsGiantSizedCreatures; }
        void setVsNonHumanoidCreature(int16_t vsNonHumanoidCreature) noexcept { _vsNonHumanoidCreatures = vsNonHumanoidCreature; }
        void setEquippedItems(size_t index, int16_t value);
        SpecialInfo_CharVersion& getSpecialInfo() noexcept { return _specialInfo; }
        void setDamageReductionVsCharm(int16_t damageReductionVsCharm) noexcept { _damageReductionVsCharm = damageReductionVsCharm; }
        void setDamageReductionVsHeat(int16_t damageReductionVsHeat) noexcept { _damageReductionVsHeat = damageReductionVsHeat; }
        void setDamageReductionVsCold(int16_t damageReductionVsCold) noexcept { _damageReductionVsCold = damageReductionVsCold; }
        void setDamageReductionVsElectric(int16_t damageReductionVsElectric) noexcept { _damageReductionVsElectric = damageReductionVsElectric; }
        void setDamageReductionVsChemical(int16_t damageReductionVsChemical) noexcept { _damageReductionVsChemical = damageReductionVsChemical; }
        void setDamageReductionVsMental(int16_t damageReductionVsMental) noexcept { _damageReductionVsMental = damageReductionVsMental; }
        void setDamageReductionVsMagic(int16_t damageReductionVsMagic) noexcept { _damageReductionVsMagic = damageReductionVsMagic; }
        void setDamageReductionVsSpecial(int16_t damageReductionVsSpecial) noexcept { _damageReductionVsSpecial = damageReductionVsSpecial; }
        void setAgeGroup(AgeGroup ageClass) noexcept { _ageClass = ageClass; }
        void setVerifyField1(int16_t verifyField1) noexcept { _verifyField1 = verifyField1; }
        void setItem(size_t index, const InventoryItem& item) noexcept;
        void setAnArrayValue(size_t index, int value);
        void setDaysOld(int32_t daysOld) noexcept { _daysOld = daysOld; }
        void setVictoryPoints(int32_t victoryPoints) noexcept { _victoryPoints = victoryPoints; }
        void setCurrentLoad(int16_t weight) noexcept { _currentLoad = weight; }
        void setMaximumLoad(int16_t field0X1F6) noexcept { _maximumLoad = field0X1F6; }
        void setGold(int16_t gold) noexcept { _gold = gold; }
        void setGems(int16_t gems) noexcept { _gems = gems; }
        void setJewelry(int16_t jewelry) noexcept { _jewelry = jewelry; }
        void setAttemptdToTurnUndeadInCombat(bool field0X1Fe) noexcept { _attemptedToTurnUndeadInCombat = field0X1Fe; }
        void setIsSpellClass1(bool isSpellClass1) noexcept { _isSpellClass1 = isSpellClass1; }
        void setIsSpellClass2(bool isSpellClass2) noexcept { _isSpellClass2 = isSpellClass2; }
        void setIsSpellClass3(bool isSpellClass3) noexcept { _isSpellClass3 = isSpellClass3; }
        void setRangedWeaponSelected(bool value) noexcept { _rangedWeaponSelected = value; }
        void setAlive(bool alive) noexcept { _alive = alive; }
        void setInAutoMode(bool aFlag) noexcept { _inAutoMode = aFlag; }
        void setBrawn(char brawn) noexcept { _brawn = brawn; }
        void setKnowledge(char knowledge) noexcept { _knowledge = knowledge; }
        void setJudgement(char judgement) noexcept { _judgement = judgement; }
        void setAgility(char agility) noexcept { _agility = agility; }
        void setVitality(char vitality) noexcept { _vitality = vitality; }
        void setLuck(char luck) noexcept { _luck = luck; }
        std::array<SpellLevel, 7>& getSpellList() noexcept { return _spellList; }
        void setName(const std::string &name) noexcept { _name = name; }
        void setPrestige(const PrestigeValues &prestige) noexcept { _prestige = prestige; }
        void setField0X304(int16_t field0X304) noexcept { _field_0x304 = field0X304; }
        void setField0X306(int16_t field0X306) noexcept { _field_0x306 = field0X306; }
        void setField0X308(int16_t field0X308) noexcept { _field_0x308 = field0X308; }
        void setField0X30A(int16_t field0X30A) noexcept { _field_0x30a = field0X30A; }
        void setField0X30C(int16_t field0X30C) noexcept { _field_0x30c = field0X30C; }
        void setField0X30E(int16_t field0X30E) noexcept { _field_0x30e = field0X30E; }
        void setField0X310(int16_t field0X310) noexcept { _field_0x310 = field0X310; }
        void setField0X312(int16_t field0X312) noexcept { _field_0x312 = field0X312; }
        void setField0X314(size_t index, int16_t value) noexcept;
        void setField0X100(size_t index, int16_t value) noexcept;
        void setTreasureArrayId(size_t index, int16_t value);
    public:
        [[nodiscard]] constexpr int16_t getLuckFromItems() const noexcept { return _luckFromItems; }
        [[nodiscard]] constexpr int16_t getBrawnFromItems() const noexcept { return _brawnFromItems; }
        [[nodiscard]] constexpr int16_t getMagicResistance() const noexcept { return _magicResistance; }
        [[nodiscard]] constexpr int16_t getMovementBonus() const noexcept { return _movementBonus; }
        [[nodiscard]] constexpr int16_t getArmorRating() const noexcept { return _armorRating; }
        [[nodiscard]] constexpr int16_t getDamagePlus() const noexcept { return _damagePlus; }
        [[nodiscard]] constexpr auto getRace() const noexcept { return _race; }
        [[nodiscard]] constexpr auto getCaste() const noexcept { return _caste; }
        [[nodiscard]] constexpr SupportedSpellClass getSupportedSpellClass() const noexcept { return _supportedSpellClass; }
        [[nodiscard]] constexpr Gender getGender() const noexcept { return _gender; }
        [[nodiscard]] constexpr int16_t getSkillLevel() const noexcept { return _skillLevel; }
        [[nodiscard]] constexpr int16_t getRemainingMovementPoints() const noexcept { return _remainingMovementPoints; }
        [[nodiscard]] constexpr int16_t getMovementPoints() const noexcept { return _movementPoints; }
        [[nodiscard]] constexpr int16_t getCombatPoints() const noexcept { return _combatPoints; }
        [[nodiscard]] constexpr int16_t getStaminaCurrent() const noexcept { return _staminaCurrent; }
        [[nodiscard]] constexpr int16_t getStaminaTotal() const noexcept { return _staminaTotal; }
        [[nodiscard]] constexpr int16_t getPortraitIndex() const noexcept { return _portraitIndex; }
        [[nodiscard]] constexpr int16_t getIconPictureIndex() const noexcept { return _iconPictureIndex; }
        [[nodiscard]] constexpr int16_t getSpellPointsCurrent() const noexcept { return _spellPointsCurrent; }
        [[nodiscard]] constexpr int16_t getSpellPointsTotal() const noexcept { return _spellPointsTotal; }
        [[nodiscard]] constexpr int16_t getHandsUsed() const noexcept { return _handsUsed; }
        [[nodiscard]] constexpr int16_t meleeWeaponIsEquipped() const noexcept { return _meleeWeaponEquipped_Probably; }
        [[nodiscard]] constexpr int16_t rangedWeaponIsEquipped() const noexcept { return _rangedWeaponEquipped_Probably; }
        [[nodiscard]] constexpr int16_t getHandToHandMax() const noexcept { return _handToHandMax; }
        [[nodiscard]] constexpr int16_t getVsMagicUsingCreatures() const noexcept { return _vsMagicUsingCreatures; }
        [[nodiscard]] constexpr int16_t getVsUndeadCreatures() const noexcept { return _vsUndeadCreatures; }
        [[nodiscard]] constexpr int16_t getVsDemonicCreatures() const noexcept { return _vsDemonicCreatures; }
        [[nodiscard]] constexpr int16_t getVsReptileCreatures() const noexcept { return _vsReptileCreatures; }
        [[nodiscard]] constexpr int16_t getVsVeryEvilCreatures() const noexcept { return _vsVeryEvilCreatures; }
        [[nodiscard]] constexpr int16_t getVsIntelligentCreatures() const noexcept { return _vsIntelligentCreatures; }
        [[nodiscard]] constexpr int16_t getVsGiantSizedCreatures() const noexcept { return _vsGiantSizedCreatures; }
        [[nodiscard]] constexpr int16_t getVsNonHumanoidCreature() const noexcept { return _vsNonHumanoidCreatures; }
        [[nodiscard]] constexpr int16_t getDamageReductionVsCharm() const noexcept { return _damageReductionVsCharm; }
        [[nodiscard]] constexpr int16_t getDamageReductionVsHeat() const noexcept { return _damageReductionVsHeat; }
        [[nodiscard]] constexpr int16_t getDamageReductionVsCold() const noexcept { return _damageReductionVsCold; }
        [[nodiscard]] constexpr int16_t getDamageReductionVsElectric() const noexcept { return _damageReductionVsElectric; }
        [[nodiscard]] constexpr int16_t getDamageReductionVsChemical() const noexcept { return _damageReductionVsChemical; }
        [[nodiscard]] constexpr int16_t getDamageReductionVsMental() const noexcept { return _damageReductionVsMental; }
        [[nodiscard]] constexpr int16_t getDamageReductionVsMagic() const noexcept { return _damageReductionVsMagic; }
        [[nodiscard]] constexpr int16_t getDamageReductionVsSpecial() const noexcept { return _damageReductionVsSpecial; }
        [[nodiscard]] constexpr auto getAgeGroup() const noexcept { return _ageClass; }
        [[nodiscard]] constexpr int16_t getVerifyField1() const noexcept { return _verifyField1; }
        [[nodiscard]] constexpr int32_t getDaysOld() const noexcept { return _daysOld; }
        [[nodiscard]] constexpr int32_t getVictoryPoints() const noexcept { return _victoryPoints; }
        [[nodiscard]] constexpr int16_t getCurrentLoad() const noexcept { return _currentLoad; }
        [[nodiscard]] constexpr int16_t getMaximumLoad() const noexcept { return _maximumLoad; }
        [[nodiscard]] constexpr int16_t getGold() const noexcept { return _gold; }
        [[nodiscard]] constexpr int16_t getGems() const noexcept { return _gems; }
        [[nodiscard]] constexpr int16_t getJewelry() const noexcept { return _jewelry; }
        [[nodiscard]] constexpr auto attemptedToTurnUndeadInCombat() const noexcept { return _attemptedToTurnUndeadInCombat; }
        [[nodiscard]] constexpr bool isIsSpellClass1() const noexcept { return _isSpellClass1; }
        [[nodiscard]] constexpr bool isIsSpellClass2() const noexcept { return _isSpellClass2; }
        [[nodiscard]] constexpr bool isIsSpellClass3() const noexcept { return _isSpellClass3; }
        [[nodiscard]] constexpr bool rangedWeaponSelected() const noexcept { return _rangedWeaponSelected; }
        [[nodiscard]] constexpr bool isAlive() const noexcept { return _alive; }
        [[nodiscard]] constexpr bool inAutoMode() const noexcept { return _inAutoMode; }
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
        [[nodiscard]] const std::array<int16_t, 6> &getField0X100() const { return _field_0x100; }
        [[nodiscard]] const std::array<SpellLevel, 7> &getSpellList() const { return _spellList; }
        [[nodiscard]] const std::string &getName() const { return _name; }
        [[nodiscard]] const PrestigeValues &getPrestige() const { return _prestige; }
        [[nodiscard]] const std::array<int16_t, 40> &getTreasureArrayIds() const { return _treasureArrayIds; }
        [[nodiscard]] const std::array<int16_t, 42> &getField0X314() const { return _field_0x314; }
        [[nodiscard]] const EquippedItems &getEquippedItems() const { return _equippedItems; }
        [[nodiscard]] const SpecialInfo_CharVersion &getSpecialInfo() const { return _specialInfo; }
        [[nodiscard]] const std::array<InventoryItem, 30> &getItems() const { return _items; }
        [[nodiscard]] const auto &getSpellsInScrollCase() const { return _spellsInScrollCase; }
        [[nodiscard]] const auto &getTotalSpellsRemaining() const { return _totalSpellsRemaining; }
        [[nodiscard]] const CharacterConditions &getConditions() const { return _conditions; }
        void print(std::ostream& os) const noexcept;
    public:
        /**
         * @brief Drop the last item in the inventory
         */
        void dropLast() noexcept;
    public:
        [[nodiscard]] constexpr auto getAgeInYears() const noexcept { return _daysOld / 365; }
        void applyAge(realmz::AgeGroup newAgeGroup, int16_t factor);
    private:
        uint16_t _id = 0;
        int16_t _verifyField0 = 0;
        int16_t _chanceToHit = 0;
        int16_t _dodgeMissile = 0;
        int16_t _missileAdjust = 0;
        int16_t _bareHandDamageMax = 0;
        int16_t _allianceClass = 0;
        int16_t _attacksPerRound = 0;
        int16_t _tookNoDamageThisRound = 0;
        int16_t _field_0x12 = 0;
        int16_t _field_0x14 = 0;
        int16_t _numItems = 0;
        int16_t _handToHandSoundIndex = 0;
        int16_t _unusedField1 = 0;
        int16_t _combatBodyIconBase = 0;
        int16_t _otherAttacksPerRoundModifier = 0;
        int16_t _vitalityFromItems = 0;
        int16_t _battleOrder = 0;
        int16_t _luckFromItems = 0;
        int16_t _brawnFromItems = 0;
        int16_t _magicResistance = 0;
        int16_t _movementBonus = 0;
        int16_t _armorRating = 0;
        int16_t _damagePlus = 0;
        RaceKind _race = RaceKind::Done;
        CasteKind _caste = CasteKind::Done;
        SupportedSpellClass _supportedSpellClass = SupportedSpellClass::None;
        Gender _gender = Gender::Undefined;
        int16_t _skillLevel = 0;
        int16_t _remainingMovementPoints = 0;
        int16_t _movementPoints = 0;
        int16_t _combatPoints = 0;
        std::array<int16_t, 7> _totalSpellsRemaining = { 0 };
        int16_t _staminaCurrent = 0;
        int16_t _staminaTotal = 0;
        int16_t _portraitIndex = 0;
        int16_t _iconPictureIndex = 0;
        int16_t _spellPointsCurrent = 0;
        int16_t _spellPointsTotal = 0;
        int16_t _handsUsed = 0;
        int16_t _meleeWeaponEquipped_Probably = 0;
        int16_t _rangedWeaponEquipped_Probably = 0;
        int16_t _handToHandMax = 0;
        CharacterConditions _conditions;
        int16_t _vsMagicUsingCreatures = 0;
        int16_t _vsUndeadCreatures = 0;
        int16_t _vsDemonicCreatures = 0;
        int16_t _vsReptileCreatures = 0;
        int16_t _vsVeryEvilCreatures = 0;
        int16_t _vsIntelligentCreatures = 0;
        int16_t _vsGiantSizedCreatures = 0;
        int16_t _vsNonHumanoidCreatures = 0;
        EquippedItems _equippedItems;
        SpecialInfo_CharVersion _specialInfo;
        std::array<int16_t, 6> _field_0x100 = { 0 };
        int16_t _turnUndeadAbility = 0;
        int16_t _field_0x10e = 0;
        int16_t _damageReductionVsCharm = 0;
        int16_t _damageReductionVsHeat = 0;
        int16_t _damageReductionVsCold = 0;
        int16_t _damageReductionVsElectric = 0;
        int16_t _damageReductionVsChemical = 0;
        int16_t _damageReductionVsMental = 0;
        int16_t _damageReductionVsMagic = 0;
        int16_t _damageReductionVsSpecial = 0;
        AgeGroup _ageClass = AgeGroup::None;
        int16_t _verifyField1 = 0;
        std::array<InventoryItem, 30> _items;
        std::array<int16_t, 10> _spellsInScrollCase = { 0 }; // it really should be 5 elements of 4 bytes each
        int32_t _daysOld = 0;
        int32_t _victoryPoints = 0;
        int16_t _currentLoad = 0;
        int16_t _maximumLoad = 0;
        int16_t _gold = 0;
        int16_t _gems = 0;
        int16_t _jewelry = 0;
        bool _attemptedToTurnUndeadInCombat = false;
        bool _isSpellClass1 = false;
        bool _isSpellClass2 = false;
        bool _isSpellClass3 = false;
        bool _rangedWeaponSelected = false;
        bool _alive = false;
        bool _inAutoMode = false;
        char _brawn = 0;
        char _knowledge = 0;
        char _judgement = 0;
        char _agility = 0;
        char _vitality = 0;
        char _luck = 0;
        std::array<SpellLevel, 7> _spellList;
        std::string _name;
        int16_t _verifyField2 = 0;
        PrestigeValues _prestige;
        std::array<int16_t, 40> _treasureArrayIds = { 0 };
        int16_t _field_0x304 = 0;
        int16_t _field_0x306 = 0;
        int16_t _field_0x308 = 0;
        int16_t _field_0x30a = 0;
        int16_t _field_0x30c = 0;
        int16_t _field_0x30e = 0;
        int16_t _field_0x310 = 0;
        int16_t _field_0x312 = 0;
        std::array<int16_t, 42> _field_0x314 = { 0 };
    };
} // end namespace realmz
std::ostream& operator<<(std::ostream& os, const realmz::Character& c) noexcept;
std::ostream& operator<<(std::ostream& os, const realmz::CharacterConditions& c) noexcept;
std::ostream& operator<<(std::ostream& os, const realmz::InventoryItem& c) noexcept;
std::ostream& operator<<(std::ostream& os, const realmz::EquippedItems& ec) noexcept;
std::ostream& operator<<(std::ostream& os, const realmz::SpecialInfo_CharVersion& ec) noexcept;
std::ostream& operator<<(std::ostream& os, const realmz::PrestigeValues& pv) noexcept;

#endif //REALMZ_TOOLS_CHARACTER_H
