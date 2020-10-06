//
// Created by jwscoggins on 10/4/20.
//

#include "Character.h"
#include <sstream>

namespace realmz {
    constexpr int8_t upperHalf(int16_t value) noexcept {
        return (value >> 8) & 0xFF;
    }
    constexpr int32_t make(int16_t lower, int16_t upper) noexcept {
        return (static_cast<int32_t>(lower) & 0x0000'FFFF) |
               ((static_cast<int32_t>(upper) << 16 )& 0xFFFF'0000);
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
            _field_0x10(buf[8]),
            _field_0x12(buf[9]),
            _field_0x14(buf[10]),
            _numItems(buf[11]),
            _field_0x18(buf[12]),
            _field_0x1a(buf[13]),
            _field_0x1c(buf[14]),
            _otherAttacksPerRoundModifier(buf[15]),
            _vitalityFromItems(buf[16]),
            _field_0x22(buf[17]),
            _luckFromItems(buf[18]),
            _brawnFromItems(buf[19]),
            _magicResistance(buf[20]),
            _movementBonus(buf[21]),
            _armorRating(buf[22]),
            _damagePlus(buf[23]),
            _race(buf[24]),
            _caste(buf[25]),
            _supportedSpellClass(static_cast<SupportedSpellClass>(buf[26])),
            _gender(static_cast<Gender>(buf[27])),
            _skillLevel(buf[28]),
            _field_0x3a(buf[29]),
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
            _field_0x5a(buf[45]),
            _field_0x5c(buf[46]),
            _field_0x5e(buf[47]),
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
                        buf[69]),
            _strong(buf[70]),
            _protectionFromFoe(buf[71]),
            _speed(buf[72]),
            _invisible(buf[73]),
            _isAnimated(buf[74]),
            _stone(buf[75]),
            _blind(buf[76]),
            _diseased(buf[77]),
            _isConfused(buf[78]),
            _reflectingSpells(buf[79]),
            _reflectingAttacks(buf[80]),
            _attackBonus(buf[81]),
            _absorbEnergy(buf[82]),
            _absorbSpellEnergyFromAttacks(buf[83]),
            _field_0xa8(buf[84]),
            _hinderedAttack(buf[85]),
            _hinderedDefense(buf[86]),
            _defensiveBonus(buf[87]),
            _affectsCastingAbility(buf[88]),
            _vsMagicUsingCreatures(buf[89]),
            _vsUndeadCreatures(buf[90]),
            _vsDemonicCreatures(buf[91]),
            _vsReptileCreatures(buf[92]),
            _vsVeryEvilCreatures(buf[93]),
            _vsIntelligentCreatures(buf[94]),
            _vsGiantSizedCreatures(buf[95]),
            _vsNonHumanoidCreature(buf[96]),
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
                    } ),
            _field_0xea(buf[117]),
            _field_0xec(buf[118]),
            _field_0xee(buf[119]),
            _field_0xf0(buf[120]),
            _specialInfo(buf[121],
                         buf[122],
                         buf[123],
                         buf[124],
                         buf[125],
                         buf[126],
                         buf[127]),
            _field_0x100( {
                                  buf[128]  ,
                                  buf[129],
                                  buf[130],
                                  buf[131],
                                  buf[132],
                                  buf[133],
                                  buf[134],
                                  buf[135]
                          }),
            _damageReductionVsCharm(buf[136]),
            _damageReductionVsHeat(buf[137]),
            _damageReductionVsCold(buf[138]),
            _damageReductionVsElectric(buf[139]),
            _damageReductionVsChemical(buf[140]),
            _damageReductionVsMental(buf[141]),
            _damageReductionVsMagic(buf[142]),
            _damageReductionVsSpecial(buf[143]),
            _ageClass(buf[144]),
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
            _anArray({
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
            _daysOld(make(buf[246], buf[247])),
            _victoryPoints(make(buf[248], buf[249])),
            _weight(buf[250]),
            _field_0x1f6(buf[251]),
            _gold(buf[252]),
            _gems(buf[253]),
            _jewelry(buf[254]),
            _field_0x1fe(upperHalf(buf[255])),
            _isSpellClass1(buf[255]),
            _isSpellClass2(upperHalf(buf[256])),
            _isSpellClass3(buf[256]),
            _itemAtIndex19IsEquipped(upperHalf(buf[257])),
            _alive(buf[257]),
            _aFlag(upperHalf(buf[258])),
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
                    make(buf[320], buf[321]),
                    make(buf[322], buf[323]),
                    make(buf[324], buf[325]),
                    make(buf[326], buf[327]),
                    make(buf[328], buf[329]),
                    make(buf[330], buf[331]),
                    make(buf[332], buf[333]),
                    make(buf[334], buf[335]),
                    make(buf[336], buf[337]),
                    make(buf[338], buf[339]),
                    make(buf[340], buf[341]),
                    make(buf[342], buf[343]),
                    make(buf[344], buf[345])),
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
    void
    Character::print(std::ostream& os) const noexcept {
        os << "Name: " << _name << std::endl;
        auto print8 = [&os](const std::string &title, int8_t value) noexcept {
            os << title << ": " << static_cast<int>(value) << std::endl;
        };
        auto print16 = [&os](const std::string &title, int16_t value) noexcept {
            os << title << ": " << static_cast<int>(value) << std::endl;
        };
        print8("Brawn", _brawn);
        print8("Knowledge", _knowledge);
        print8("Judgement", _judgement);
        print8("Agility", _agility);
        print8("Vitality", _vitality);
        print8("Luck", _luck);
        print16("Verify0", _verifyField0);
        print16("Verify1", _verifyField1);
        print16("Verify2", _verifyField2);
        print16("Chance to hit", _chanceToHit);
        print16("Dodge Missile", _dodgeMissile);
        print16("Movement Points", _movementPoints);
        print16("Missile Adjust", _missileAdjust);
        print16("Bare Hand Damage Max", _bareHandDamageMax);
        print16("Alliance Class", _allianceClass);
        print16("Attacks Per Round", _attacksPerRound);
        print16("Field 0x10", _field_0x10);
        print16("Field 0x12", _field_0x12);
        print16("Field 0x14", _field_0x14);
        os << _conditions << std::endl;
        print16("Num Items", _numItems);
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
    }
    void
    EquippedItems::print(std::ostream &os) const noexcept {
        os << "Equipped Items {" << std::endl;
        auto fn = [&os](const std::string& name, int16_t value) noexcept {
            os << "\t" << name << ": ";
            if (value != 0) {
                os << std::dec << value;
            } else {
                os << "Unequipped";
            }
            os << std::endl;
        };
        fn("Field 0", _field0);
        fn("Field 1", _field1);
        fn("Field 2", _field2);
        fn("Field 3", _field3);
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
        fn("Field 17", _field17);
        fn("Field 18", _field18);
        fn("Field 19", _field19);
        os << "}" << std::endl;
    }

    void
    CharacterConditions::print(std::ostream &os) const noexcept {
        os << "Conditions: {" << std::endl;
        auto fn = [&os](const std::string& title, int16_t value) noexcept {
            os << "\t" << title << ": " << value << std::endl;
        };
        fn("In Retreat", _inRetreat);
        fn("Helpless", _helpless);
        fn("Tangled", _tangled);
        fn("Cursed", _isCursed);
        fn("Magic Aura", _conditionMagicAura);
        fn("Stupid or Silenced", _supidOrSilenced1);
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
        os << "}";
    }

    void
    InventoryItem::print(std::ostream &os) const noexcept {
        os << "{" << std::dec << "Index: " << _idx <<
        ", Field2: " << std::dec << static_cast<int>(_f2) <<
        ", Field3: " << std::dec << static_cast<int>(_f3) <<
        ", Flags: " << std::hex << _flags << "}";
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
