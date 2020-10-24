//
// Created by jwscoggins on 10/4/20.
//

#include "Character.h"
#include "Utilities.h"
#include "RaceData.h"
#include "AgeGroup.h"
#include <sstream>

namespace realmz {
    std::string consumeName(const std::array<char, 31>& chars) noexcept {
        std::stringstream ss;
        for (auto c : chars) {
            if (c == 0)  {
                break;
            } else {
                ss << c;
            }
        }
        auto str = ss.str();
        return str;
    }
    constexpr int32_t makeSwapped(int16_t upper, int16_t lower) noexcept {
        return make(lower, upper, ConstructInt32{});
    }
    Character::Character(const CharacterDataBuffer &buf) :
            _id(buf[0]),
            _verifyField0(buf[1]),
            _chanceToHit(buf[2]),
            _dodgeMissile(buf[3]),
            _missileAdjust(buf[4]),
            _bareHandDamageMax(buf[5]),
            _allianceClass(buf[6]),
            _attacksPerRound(buf[7]),
            _tookNoDamageThisRound(buf[8]),
            _field_0x12(buf[9]),
            _field_0x14(buf[10]),
            _numItems(buf[11]),
            _handToHandSoundIndex(buf[12]),
            _unusedField1(buf[13]),
            _combatBodyIconBase(buf[14]),
            _otherAttacksPerRoundModifier(buf[15]),
            _vitalityFromItems(buf[16]),
            _battleOrder(buf[17]),
            _luckFromItems(buf[18]),
            _brawnFromItems(buf[19]),
            _magicResistance(buf[20]),
            _movementBonus(buf[21]),
            _armorRating(buf[22]),
            _damagePlus(buf[23]),
            _race(static_cast<RaceKind>(buf[24])),
            _caste(static_cast<CasteKind>(buf[25])),
            _supportedSpellClass(static_cast<SupportedSpellClass>(buf[26])),
            _gender(static_cast<Gender>(buf[27])),
            _skillLevel(buf[28]),
            _remainingMovementPoints(buf[29]),
            _movementPoints(buf[30]),
            _combatPoints(buf[31]),
            _totalSpellsRemaining({
                                          buf[32],
                                          buf[33],
                                          buf[34],
                                          buf[35],
                                          buf[36],
                                          buf[37],
                                          buf[38]
                                  }),
            _staminaCurrent(buf[39]),
            _staminaTotal(buf[40]),
            _portraitIndex(buf[41]),
            _iconPictureIndex(buf[42]),
            _spellPointsCurrent(buf[43]),
            _spellPointsTotal(buf[44]),
            _handsUsed(buf[45]),
            _meleeWeaponEquipped_Probably(buf[46]),
            _rangedWeaponEquipped_Probably(buf[47]),
            _handToHandMax(buf[48]),
            _conditions(buf[49],
                        buf[50],
                        buf[51],
                        buf[52],
                        buf[53],
                        buf[54],
                        buf[55],
                        buf[56],
                        buf[57],
                        buf[58],
                        buf[59],
                        buf[60],
                        buf[61],
                        buf[62],
                        buf[63],
                        buf[64],
                        buf[65],
                        buf[66],
                        buf[67],
                        buf[68],
                        buf[69],
                        buf[70],
                        buf[71],
                        buf[72],
                        buf[73],
                        buf[74],
                        buf[75],
                        buf[76],
                        buf[77],
                        buf[78],
                        buf[79],
                        buf[80],
                        buf[81],
                        buf[82],
                        buf[83],
                        buf[84],
                        buf[85],
                        buf[86],
                        buf[87],
                        buf[88]),
            _vsMagicUsingCreatures(buf[89]),
            _vsUndeadCreatures(buf[90]),
            _vsDemonicCreatures(buf[91]),
            _vsReptileCreatures(buf[92]),
            _vsVeryEvilCreatures(buf[93]),
            _vsIntelligentCreatures(buf[94]),
            _vsGiantSizedCreatures(buf[95]),
            _vsNonHumanoidCreatures(buf[96]),
            _equippedItems(
                    {
                            buf[97],
                            buf[98],
                            buf[99],
                            buf[100],
                            buf[101],
                            buf[102],
                            buf[103],
                            buf[104],
                            buf[105],
                            buf[106],
                            buf[107],
                            buf[108],
                            buf[109],
                            buf[110],
                            buf[111],
                            buf[112],
                            buf[113],
                            buf[114],
                            buf[115],
                            buf[116],
                            buf[117],
                            buf[118],
                            buf[119],
                            buf[120]
                    } ),
            _specialInfo(buf[121],
                         buf[122],
                         buf[123],
                         buf[124],
                         buf[125],
                         buf[126],
                         buf[127],
                         buf[128],
                         buf[129],
                         buf[130],
                         buf[131],
                         buf[132],
                         buf[133],
                         buf[134],
                         buf[135]),
            _damageReductionVsCharm(buf[136]),
            _damageReductionVsHeat(buf[137]),
            _damageReductionVsCold(buf[138]),
            _damageReductionVsElectric(buf[139]),
            _damageReductionVsChemical(buf[140]),
            _damageReductionVsMental(buf[141]),
            _damageReductionVsMagic(buf[142]),
            _damageReductionVsSpecial(buf[143]),
            _ageClass(static_cast<AgeGroup>(buf[144])),
            _verifyField1(buf[145]),
            _items( {
#define X(offset) InventoryItem(buf[(3*offset) + 146], upperHalf(buf[(3*offset) + 147]), buf[(3*offset) + 147], buf[(3*offset) + 148] )
                            X(0),
                            X(1),
                            X(2),
                            X(3),
                            X(4),
                            X(5),
                            X(6),
                            X(7),
                            X(8),
                            X(9),
                            X(10),
                            X(11),
                            X(12),
                            X(13),
                            X(14),
                            X(15),
                            X(16),
                            X(17),
                            X(18),
                            X(19),
                            X(20),
                            X(21),
                            X(22),
                            X(23),
                            X(24),
                            X(25),
                            X(26),
                            X(27),
                            X(28),
                            X(29),
#undef X
                    }),
            _spellsInScrollCase({
                                        buf[236],
                                        buf[237],
                                        buf[238],
                                        buf[239],
                                        buf[240],
                                        buf[241],
                                        buf[242],
                                        buf[243],
                                        buf[244],
                                        buf[245],
                                }),
            _daysOld(makeSwapped(buf[246], buf[247])),
            _victoryPoints(makeSwapped(buf[248], buf[249])),
            _currentLoad(buf[250]),
            _maximumLoad(buf[251]),
            _gold(buf[252]),
            _gems(buf[253]),
            _jewelry(buf[254]),
            _attemptedToTurnUndeadInCombat(upperHalf(buf[255])),
            _isSpellClass1(buf[255]),
            _isSpellClass2(upperHalf(buf[256])),
            _isSpellClass3(buf[256]),
            _rangedWeaponSelected(upperHalf(buf[257])),
            _alive(buf[257]),
            _inAutoMode(upperHalf(buf[258])),
            _brawn(buf[258]),
            _knowledge(upperHalf(buf[259])),
            _judgement(buf[259]),
            _agility(upperHalf(buf[260])),
            _vitality(buf[260]),
            _luck(upperHalf(buf[261])),
            _spellList({
#define X(base) SpellLevel { \
                    static_cast<bool>(buf[base]), static_cast<bool>(upperHalf(buf[base+1])), \
                               static_cast<bool>(buf[base+1]), static_cast<bool>(upperHalf(buf[base+2])), \
                               static_cast<bool>(buf[base+2]), static_cast<bool>(upperHalf(buf[base+3])), \
                               static_cast<bool>(buf[base+3]), static_cast<bool>(upperHalf(buf[base+4])), \
                               static_cast<bool>(buf[base+4]), static_cast<bool>(upperHalf(buf[base+5])), \
                               static_cast<bool>(buf[base+5]), static_cast<bool>(upperHalf(buf[base+6]))  \
                }
                               X(261),
                               X(267),
                               X(273),
                               X(279),
                               X(285),
                               X(291),
                               X(297),
#undef X
                       }),
            _name({
                          static_cast<char>(buf[303]),
#define X(offset) static_cast<char>(upperHalf(buf[offset])), static_cast<char>(buf[offset])
                          X(304), // each one of these consumes two characters so we should only do 15 of these entries
                          X(305),
                          X(306),
                          X(307),
                          X(308),
                          X(309),
                          X(310),
                          X(311),
                          X(312),
                          X(313),
                          X(314),
                          X(315),
                          X(316),
                          X(317),
                          X(318)
#undef X
                  }),
            _verifyField2(buf[319]),
            _prestige(
                    makeSwapped(buf[320], buf[321]),
                    makeSwapped(buf[322], buf[323]),
                    makeSwapped(buf[324], buf[325]),
                    makeSwapped(buf[326], buf[327]),
                    makeSwapped(buf[328], buf[329]),
                    makeSwapped(buf[330], buf[331]),
                    makeSwapped(buf[332], buf[333]),
                    makeSwapped(buf[334], buf[335]),
                    makeSwapped(buf[336], buf[337]),
                    makeSwapped(buf[338], buf[339]),
                    makeSwapped(buf[340], buf[341]),
                    makeSwapped(buf[342], buf[343]),
                    makeSwapped(buf[344], buf[345])),
            _treasureArrayIds({
#define X10(offset) buf[offset], buf[offset+1], buf[offset+2], buf[offset+3], buf[offset+4], buf[offset+5], buf[offset+6], buf[offset+7], buf[offset+8], buf[offset+9]
                                      X10(346),
                                      X10(356),
                                      X10(366),
                                      X10(376)
#undef X10
                              }),
            _field_0x304(buf[386]),
            _field_0x306(buf[387]),
            _field_0x308(buf[388]),
            _field_0x30a(buf[389]),
            _field_0x30c(buf[390]),
            _field_0x30e(buf[391]),
            _field_0x310(buf[392]),
            _field_0x312(buf[393]),
            _field_0x314({
#define X10(offset) buf[offset], buf[offset+1], buf[offset+2], buf[offset+3], buf[offset+4], buf[offset+5], buf[offset+6], buf[offset+7], buf[offset+8], buf[offset+9]
                                 X10(394),
                                 X10(404),
                                 X10(414),
                                 X10(424),
#undef X10
                                 buf[434],
                                 buf[435],

                         })
    {

    }
    template<typename T>
    void printOut(std::ostream& os, const std::string& title, T value, bool indent = false) noexcept {
        using K = std::decay_t<T>;
        if (indent) {
            os << "\t";
        }
        os << title << ": ";
        if constexpr (std::is_same_v<K, int8_t> || std::is_same_v<K, uint8_t> || std::is_same_v<K, int16_t> || std::is_same_v<K, uint16_t> || std::is_same_v<K, char> || std::is_same_v<K, unsigned char>) {
            os << std::dec << static_cast<int>(value);
        } else if constexpr (std::is_same_v<K, bool>) {
           os << std::boolalpha << value;
        } else {
            os << std::dec << value;
        }
        os << std::endl;
    }
    void
    Character::print(std::ostream& os) const noexcept {
        os << "Name: " << _name << std::endl;
        printOut(os, "Brawn", _brawn);
        printOut(os, "Knowledge", _knowledge);
        printOut(os, "Judgement", _judgement);
        printOut(os, "Agility", _agility);
        printOut(os, "Vitality", _vitality);
        printOut(os, "Luck", _luck);
        printOut(os, "Verify0", _verifyField0);
        printOut(os, "Verify1", _verifyField1);
        printOut(os, "Verify2", _verifyField2);
        printOut(os, "Chance to hit", _chanceToHit);
        printOut(os, "Dodge Missile", _dodgeMissile);
        printOut(os, "Movement Points", _movementPoints);
        printOut(os, "Missile Adjust", _missileAdjust);
        printOut(os, "Bare Hand Damage Max", _bareHandDamageMax);
        printOut(os, "Alliance Class", _allianceClass);
        printOut(os, "Attacks Per Round", _attacksPerRound);
        printOut(os, "Took No Damage This Round?", _tookNoDamageThisRound);
        printOut(os, "Field 0x12", _field_0x12);
        printOut(os, "Field 0x14", _field_0x14);
        os << _conditions << std::endl;
        printOut(os, "Num Items", _numItems);
        os << "{" << std::endl;
        int index = 1;
        for (const auto &ii : _items) {
            if (ii.getIndex() != 0) {
                os << "\t" << std::dec << index << ": " << ii << std::endl;
            }
            ++index;
        }
        os << "}" << std::endl;
        os << _equippedItems << std::endl;
        printOut(os, "Hand to Hand sound index", _handToHandSoundIndex);
        printOut(os, "Unused Field 1", _unusedField1);
        printOut(os, "Combat Body Icon Base", _combatBodyIconBase);
        printOut(os, "Other Attacks Per Round Modifier", _otherAttacksPerRoundModifier);
        printOut(os, "Vitality from Items", _vitalityFromItems);
        printOut(os, "Battle Order", _battleOrder);
        printOut(os, "Luck from Items", _luckFromItems);
        printOut(os, "Brawn from Items", _brawnFromItems);
        printOut(os, "Magic Resistance", _magicResistance);
        printOut(os, "Movement Bonus", _movementBonus);
        printOut(os, "Armor Rating", _armorRating);
        printOut(os, "Damage Plus",_damagePlus);
        printOut(os, "Race", _race);
        printOut(os, "Caste", _caste);
        printOut(os, "Supported Spell Class", static_cast<int16_t>(_supportedSpellClass));
        printOut(os, "Gender", static_cast<int16_t>(_gender));
        printOut(os, "Skill Level", _skillLevel);
        printOut(os, "Remaining Movement Points", _remainingMovementPoints);
        printOut(os, "Movement Points", _movementPoints);
        printOut(os, "Combat Points", _combatPoints);
        index = 1;
        for (const auto ts : _totalSpellsRemaining) {
            os << "Spell Level " << std::dec << index << " Spells Remaining: " <<  static_cast<int>(ts) << std::endl;
            ++index;
        }
        printOut(os, "Stamina Current", _staminaCurrent);
        printOut(os, "Stamina Total", _staminaTotal);
        printOut(os, "Portrait Index", _portraitIndex);
        printOut(os, "Icon Picture Index", _iconPictureIndex);
        printOut(os, "Spell Points Current", _spellPointsCurrent);
        printOut(os, "Spell Points Total", _spellPointsTotal);
        printOut(os, "Hands Used", _handsUsed);
        printOut(os, "Melee Weapon Equipped (Probably)", _meleeWeaponEquipped_Probably);
        printOut(os, "Ranged Weapon Equipped (Probably)", _rangedWeaponEquipped_Probably);
        printOut(os, "Hand To Hand Max", _handToHandMax);
        printOut(os, "VS Magic Using Creatures", _vsMagicUsingCreatures);
        printOut(os, "VS Undead Creatures", _vsUndeadCreatures);
        printOut(os, "VS Demonic Creatures", _vsDemonicCreatures);
        printOut(os, "VS Reptile Creatures", _vsReptileCreatures);
        printOut(os, "VS Very Evil Creatures", _vsVeryEvilCreatures);
        printOut(os, "VS Giant Sized Creatures", _vsGiantSizedCreatures);
        printOut(os, "VS Non Humanoid Creatures", _vsNonHumanoidCreatures);
        os << _specialInfo;

        auto printDRV = [&os](const std::string& kind, uint16_t value) noexcept {
            std::stringstream ss;
            ss << "Damage Reduction Vs " << kind;
            auto str = ss.str();
            printOut(os, str, value);
        };
        printDRV("Charm", _damageReductionVsCharm);
        printDRV("Heat", _damageReductionVsHeat);
        printDRV("Cold", _damageReductionVsCold);
        printDRV("Electric", _damageReductionVsElectric);
        printDRV("Chemical", _damageReductionVsChemical);
        printDRV("Mental", _damageReductionVsMental);
        printDRV("Magic", _damageReductionVsMagic);
        printDRV("Special", _damageReductionVsSpecial);
        printOut(os, "Age Class", _ageClass);
        /// @todo printout spells in scroll case
        printOut(os, "Days Old", _daysOld);
        os << "\tAge in Years: " << getAgeInYears() << std::endl;
        printOut(os, "Victory Points", _victoryPoints);
        printOut(os, "Current Load", _currentLoad);
        printOut(os, "Maximum Load", _maximumLoad);
        printOut(os, "Gold", _gold);
        printOut(os, "Gems", _gems);
        printOut(os, "Jewelry", _jewelry);
        printOut(os, "Attempted To Turn Undead In Combat", _attemptedToTurnUndeadInCombat);
        printOut(os, "Is Spell Class 1", _isSpellClass1);
        printOut(os, "Is Spell Class 2", _isSpellClass2);
        printOut(os, "Is Spell Class 3", _isSpellClass3);
        printOut(os, "Alive", _alive);
        printOut(os, "In Auto Mode", _inAutoMode);
        os << _prestige ;
    };
    void
    EquippedItems::print(std::ostream &os) const noexcept {
        static constexpr bool PrintUnusedFields = false;
        os << "Equipped Items {" << std::endl;
        auto fn = [&os](const std::string &name, int16_t value) noexcept {
            os << "\t" << name << ": ";
            if (value != 0) {
                os << std::dec << value;
            } else {
                os << "Unequipped";
            }
            os << std::endl;
        };
        if constexpr (PrintUnusedFields) {
            fn("Field 0", _unused0);
            fn("Field 1", _unused1);
            fn("Field 2", _unused2);
            fn("Field 3", _unused3);
        }
        fn("Ring 0", _ring0);
        fn("Ring 1", _ring1);
        fn("Weapon", _weapon);
        fn("Shield", _shield);
        fn("Armor", _armor);
        fn("Gauntlets", _gauntlets);
        fn("Cloak", _cloak);
        fn("Helm", _helm);
        fn("Luck Stone/Totem", _luckStone);
        fn("Boots", _boots);
        fn("Quiver", _quiver);
        fn("Belt", _belt);
        fn("Necklace", _necklace);
        fn("Scroll Case", _scrollCase);
        if constexpr (PrintUnusedFields) {
            fn("Unused 4", _unused4);
        }
        fn("Bow", _bow);
        if constexpr (PrintUnusedFields) {
            fn("Unused 5", _unused5);
            fn("Unused 6", _unused6);
            fn("Unused 7", _unused7);
            fn("Unused 8", _unused8);
        }
        os << "}" << std::endl;
    }

    void
    CharacterConditions::print(std::ostream &os) const noexcept {
        os << "Conditions: {" << std::endl;
        auto fn = [&os](const std::string& title, int16_t value) noexcept {
            if (value != 0) {
                printOut(os, title, value, true);
            }
        };
        fn("In Retreat", _inRetreat);
        fn("Helpless", _helpless);
        fn("Tangled", _tangled);
        fn("Cursed", _isCursed);
        fn("Magic Aura", _conditionMagicAura);
        fn("Stupid", _stupid);
        fn("Slow", _isSlow);
        fn("Shielded From Normal Attacks", _conditionShieldedFromNormalAttacks);
        fn("Shielded From Projectiles", _conditionShieldedFromProjectiles);
        fn("Poisoned", _poisoned);
        fn("Regenerating", _regenerating);
#define X(kind) fn("Protection from " #kind " Attacks", _protectionFrom ## kind ## Attacks)
#define Y(kind) fn("Protection from " #kind " Level Spells", _protectionFrom ## kind ## LevelSpells)
        X(Heat);
        X(Cold);
        X(Electrical);
        X(Chemical);
        X(Mental);
        Y(1st);
        Y(2nd);
        Y(3rd);
        Y(4th);
        Y(5th);
#undef Y
#undef X
        fn("Strong", _strong);
        fn("Protection from Foe", _protectionFromFoe);
        fn("Speedy", _speedy);
        fn("Invisible", _invisible);
        fn("Animated", _isAnimated);
        fn("Stone", _stone);
        fn("Blind", _blind);
        fn("Diseased", _diseased);
        fn("Confused", _confused);
        fn("Reflecting Spells", _reflectingSpells);
        fn("Reflecting Attacks", _reflectingAttacks);
        fn("Bonus Damage", _bonusDamage);
        fn("Absorb Energy", _absorbEnergy);
        fn("Energy Draining", _energyDraining);
        fn("Absorb Spell Energy From Attacks", _absorbSpellEnergyFromAttacks);
        fn("Hindered Attack", _hinderedAttack);
        fn("Hindered Defense", _hinderedDefense);
        fn("Defense Bonus", _defensiveBonus);
        fn("Silenced", _silenced);
        os << "}";
    }

    void
    InventoryItem::print(std::ostream &os) const noexcept {
        os << "{" << std::dec << "Index: " << _idx <<
           ", Equipped: " << std::boolalpha << _equipped <<
           ", Field3: " << std::dec << static_cast<int>(_f3) <<
           ", Flags: " << std::hex << _flags << "}";
    }

    void
    SpecialInfo::print(std::ostream &os) const noexcept {
        printOut(os, "Sneak Attack", _sneakAttack);
        printOut(os, "Cause Major Wound", _causeMajorWound);
        printOut(os, "Detect Secret", _detectSecret);
        printOut(os, "Acrobatic Act", _acrobaticAct);
        printOut(os, "Detect Trap", _detectTrap);
        printOut(os, "Disable Trap", _disableTrap);
        printOut(os, "Force Lock", _forceLock);
        printOut(os, "Pick Lock", _pickLock);
        printOut(os, "Turn Undead", _turnUndead);
    }

    void
    PrestigeValues::print(std::ostream &os) const noexcept {
        os << "Current Prestige: " << getCurrentPrestige() << std::endl;
        os << "Prestige Values {" << std::endl;
        printOut(os, "Damage Taken", _damageTaken, true);
        printOut(os, "Damage Given", _damageGiven, true);
        printOut(os, "Hits Taken", _hitsTaken, true);
        printOut(os, "Hits Given", _hitsGiven, true);
        printOut(os, "Missed Attacks", _missedAttacks, true);
        printOut(os, "Dodged Attacks", _dodgedAttacks, true);
        printOut(os, "Enemies Killed", _enemiesKilled, true);
        printOut(os, "Times Died", _timesDied, true);
        printOut(os, "Times Unconscious", _timesUnconscious, true);
        printOut(os, "Combat Spells Cast", _combatSpellsCast, true);
        printOut(os, "Undead Destroyed", _undeadDestroyed, true);
        printOut(os, "Undead Turned", _undeadTurned, true);
        printOut(os, "Penalty Points", _penaltyPoints, true);
        os << "}" << std::endl;
    }

    void
    Character::dropLast() noexcept {
        // drop the last item in the inventory
    }

    void
    Character::applyAge(AgeGroup newAgeGroup, int16_t factor) {
        if (!legalValue(newAgeGroup)) {
            throw "Illegal age group presented!";
        }
        auto& targetRace = loadRaceData(_race);
        _ageClass = newAgeGroup;
        auto index = static_cast<size_t>(newAgeGroup) - 1;
        auto& targetAgeModifier = targetRace.getAgeModifier(index);
        _brawn += targetAgeModifier.getBrawn() * factor;
        _knowledge += targetAgeModifier.getKnowledge() * factor;
        _judgement += targetAgeModifier.getJudgment() * factor;
        _agility += targetAgeModifier.getAgility() * factor;
        _vitality += targetAgeModifier.getVitality() * factor;
        _luck +=  targetAgeModifier.getLuck() * factor;
        _magicResistance += targetAgeModifier.getMagicResist() * factor;
        _movementPoints += targetAgeModifier.getMovement() * factor;
        _damageReductionVsCharm += targetAgeModifier.getCharm() * factor;
        _damageReductionVsMagic += targetAgeModifier.getMagical() * factor;
        _damageReductionVsElectric += targetAgeModifier.getElectrical() * factor;
        _damageReductionVsCold += targetAgeModifier.getCold() * factor;
        _damageReductionVsHeat += targetAgeModifier.getHeat() * factor;
        _damageReductionVsChemical += targetAgeModifier.getChemical() * factor;
        _damageReductionVsMental += targetAgeModifier.getMental() * factor;
    }
}

std::ostream&
operator<<(std::ostream& os, const realmz::Character& c) noexcept {
    c.print(os);
    return os;
}
std::ostream&
operator<<(std::ostream& os, const realmz::CharacterConditions& c) noexcept {
    c.print(os);
    return os;
}

std::ostream&
operator<<(std::ostream& os, const realmz::InventoryItem& ii) noexcept {
    ii.print(os);
    return os;
}

std::ostream&
operator<<(std::ostream& os, const realmz::EquippedItems& eq) noexcept {
    eq.print(os);
    return os;
}

std::ostream&
operator<<(std::ostream& os, const realmz::SpecialInfo& eq) noexcept {
    eq.print(os);
    return os;
}

std::ostream&
operator<<(std::ostream& os, const realmz::PrestigeValues& eq) noexcept {
    eq.print(os);
    return os;
}
