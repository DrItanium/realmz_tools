//
// Created by jwscoggins on 9/20/20.
//

#include "Caste.h"

namespace realmz {
    SpecialAbilities::SpecialAbilities(const CasteDataBuffer &buf) :
            _sneakAttack(buf[0], buf[14]),
            _majorWound(buf[3], buf[14 + 3]),
            _detectSecret(buf[4], buf[14 + 4]),
            _acrobaticAct(buf[5], buf[14 + 5]),
            _detectTrap(buf[6], buf[14 + 6]),
            _disableTrap(buf[7], buf[14 + 7]),
            _forceLock(buf[9], buf[14 + 9]),
            _pickLock(buf[11], buf[14 + 11]),
            _turnUndead(buf[13], buf[14 + 13]) {
    }
    void
    SpecialAbilities::print(std::ostream &os) const noexcept {
#define X(field) os << #field << ": " <<  _ ## field << std::endl
        X(sneakAttack);
        X(majorWound);
        X(detectSecret);
        X(acrobaticAct);
        X(detectTrap);
        X(disableTrap);
        X(forceLock);
        X(pickLock);
        X(turnUndead);
#undef X
    }
    void
    SpellClassInfo::print(std::ostream &out) const noexcept {
        out << "(" << std::boolalpha << _enabled << ", " << std::dec << _startingLevel << ", " << _maxLevelSpells << ")";
    }
    Caste::Caste(const CasteDataBuffer &buffer) :
            _initial(buffer),
            _drvs(buffer),
            _attributes(buffer),
            _spellCasting(buffer),
            _conditions(buffer),
            _canUseMissileWeapons(buffer[106]),
            _getsMissileBonusDamage(buffer[107]),
            _stamina(buffer[108], buffer[109]),
// skip buffer 110 and 111 for now, unsure what it is for
            _dodgeMissile(buffer[112], buffer[113]),
            _meleeAttack(buffer[114], buffer[115]),
            _missileAttack(buffer[116], buffer[117]),
            _handToHand(buffer[118], buffer[119]),
            _inelegibilityIndex(buffer[124]),
            _startingAgeGroup(static_cast<AgeGroup>(buffer[125])),
            _movementPoints(buffer[126]),
            _magicResistance(buffer[127]),
            _twoHandedAdjust(buffer[128]),
            _maxStaminaBonus(buffer[129]),
            _bonusAttacks(static_cast<BonusAttacksStyle>(buffer[130])),
            _maxAttacksPerRound(buffer[131]),
            _victoryPointsAtLevel(buffer)
    {}

    void
    Caste::print(std::ostream &os) const noexcept {
        os << _initial << _drvs << _attributes << _spellCasting << _conditions;
        os << "Can Use Missile Weapons: " << std::boolalpha << _canUseMissileWeapons << std::endl;
        os << "Gets Missile Bonus Damage: " << std::boolalpha << _getsMissileBonusDamage << std::endl;
        os << "Stamina: " << _stamina << std::endl;
        os << "Dodge Missile: " << _dodgeMissile << std::endl;
        os << "Melee Attack: " << _meleeAttack << std::endl;
        os << "Missile Attack: " << _missileAttack << std::endl;
        os << "Hand To Hand: " << _handToHand << std::endl;
        os << "Inelegibility Index?: " << _inelegibilityIndex << std::endl;
        os << "Starting Age Group: " << _startingAgeGroup << std::endl;
        os << "Movement Point Modification: " << _movementPoints << std::endl;
        os << "Magic Resistance Modification: " << _magicResistance << std::endl;
        os << "Two Handed Adjust: " << _twoHandedAdjust << std::endl;
        os << "Max Stamina Bonus: " << _maxStaminaBonus << std::endl;
        os << "Bonus Attacks: " << _bonusAttacks << std::endl;
        os << "Max Attacks per Round: " << _maxAttacksPerRound << std::endl;
        os << _victoryPointsAtLevel << std::endl;
    }
    SpellCastingAbilities::SpellCastingAbilities(const CasteDataBuffer &buf) :
            _sorcerer(buf[42], buf[43], buf[44]),
            _priest(buf[45], buf[46], buf[47]),
            _enchanter(buf[48], buf[49], buf[50]),
            _unused(buf[51], buf[52], buf[53]) {}
    void
    SpellCastingAbilities::print(std::ostream &out) const noexcept {
        out << "Sorcerer: " << _sorcerer << std::endl;
        out << "Priest: " << _priest << std::endl;
        out << "Enchanter: " << _enchanter << std::endl;
        out << "Unused: " << _unused << std::endl;
     }
    void
    Attributes::print(std::ostream &out) const noexcept
    {
        out << "Brawn: " << _brawn << std::endl;
        out << "Knowledge: " << _knowledge << std::endl;
        out << "Judgment: " << _judgment << std::endl;
        out << "Agility: " << _agility << std::endl;
        out << "Vitality: " << _vitality << std::endl;
        out << "Luck: " << _luck << std::endl;
    }
    Attributes::Attributes(const CasteDataBuffer &buf) :
            _brawn(buf[54], buf[55], buf[36]),
            _knowledge(buf[56], buf[57], buf[37]),
            _judgment(buf[58], buf[59], buf[38]),
            _agility(buf[60], buf[61], buf[39]),
            _vitality(buf[62], buf[63], buf[40]),
            _luck(buf[64], buf[65], buf[41]) {

    }
    DRVAdjustments::DRVAdjustments(const CasteDataBuffer &buf) : _charm(buf[28]), _heat(buf[29]), _cold(buf[30]), _electric(buf[31]), _chemical(buf[32]), _mental(buf[33]), _magical(buf[34]) {}
    void
    DRVAdjustments::print(std::ostream &os) const noexcept {
#define X(field) \
            os << #field << ": " << _ ## field << std::endl
        X(charm);
        X(heat);
        X(cold);
        X(electric);
        X(chemical);
        X(mental);
        X(magical);
#undef X
    }
    void
    Attribute::print(std::ostream &os) const noexcept {
        os << "(" << _min << ", " << _max << ", " << _adjustment << ")";
    }

    void
    VictoryPoints::print(std::ostream &os) const noexcept {
        os << "Victory Points @ Level {" << std::endl;
        int index = 0;
        for (const auto& value : _contents) {
            os << "\t" << std::dec << index << ": " <<  std::dec << value << std::endl;
        }
        os << "}" << std::endl;
    }
    VictoryPoints::VictoryPoints(const CasteDataBuffer &buf) {
        constexpr auto startPosition = 264 / 2;
        constexpr auto endPosition = startPosition + (30 * 2); // these are int32_t's
        for (int i = startPosition; i < endPosition; i+=2) {
            // eliminate sign extension by making it unsigned
            auto lower = static_cast<int32_t>(buf[i]) & 0xFFFF;
            auto upper = static_cast<int32_t>(buf[i + 1]) & 0xFFFF;
            _contents.emplace_back(lower | (upper << 16));

        }
    }
} // end namespace realmz
std::ostream &operator<<(std::ostream &os, const realmz::Caste &caste) noexcept {
    caste.print(os);
    return os;
}
std::ostream &
operator<<(std::ostream &os, realmz::CasteKind ck) noexcept {
    switch (ck) {
#define X(field, str) case realmz::CasteKind:: field : os << str; break
#define Y(field) X(field, #field)
        Y(Fencer);
        Y(Fighter);
        Y(Monk);
        Y(Crusader);
        Y(Archer);
        Y(Rogue);
        Y(Sorcerer);
        Y(Priest);
        Y(Enchanter);
        Y(Evoker);
        Y(Cardinal);
        Y(Cabalist);
        Y(Berzerker);
        Y(Bard);
        Y(Marksman);
        Y(Assassin);
        Y(Dabbler);
        X(BattleMage, "Battle Mage");
        Y(Warlock);
        Y(Minstrel);
#undef Y
#undef X
        default:
            os << "UNKNOWN_CASTE_KIND(" << static_cast<int>(ck) << ")";
            break;
    }
    return os;
}
std::ostream &operator<<(std::ostream &os, const realmz::Attribute &ca) noexcept {
    ca.print(os);
    return os;
}
std::ostream &
operator<<(std::ostream &os, realmz::BonusAttacksStyle group) noexcept {
    switch (group) {
        case realmz::BonusAttacksStyle::None:
            os << "0";
            break;
        case realmz::BonusAttacksStyle::OneHalf:
            os << "1/2";
            break;
        case realmz::BonusAttacksStyle::One:
            os << "1";
            break;
        case realmz::BonusAttacksStyle::OneAndOneHalf:
            os << "1 1/2";
            break;
        case realmz::BonusAttacksStyle::Two:
            os << "2";
            break;
        default:
            os << "UNKNOWN_BONUS_ATTACK_STYLE(" << static_cast<int>(group) << ")!";
            break;
    }
    return os;
}
std::ostream &operator<<(std::ostream &os, const realmz::SpellCastingAbilities &sci) noexcept {
    sci.print(os);
    return os;
}
std::ostream &operator<<(std::ostream &os, const realmz::DRVAdjustments &drv) noexcept {
    drv.print(os);
    return os;
}
std::ostream &operator<<(std::ostream &os, realmz::AgeGroup group) noexcept {
    switch (group) {
        case realmz::AgeGroup::Youth:
            os << "Youth";
            break;
        case realmz::AgeGroup::Young:
            os << "Young";
            break;
        case realmz::AgeGroup::Prime:
            os << "Prime";
            break;
        case realmz::AgeGroup::Adult:
            os << "Adult";
            break;
        case realmz::AgeGroup::Senior:
            os << "Senior";
            break;
        default:
            os << "UNKNOWN_AGE_GROUP(" << static_cast<int>(group) << ")!";
            break;
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const realmz::Attributes &attrib) noexcept {
    attrib.print(os);
    return os;
}
std::ostream &operator<<(std::ostream &os, const realmz::SpecialAbilities &sa) noexcept {
    sa.print(os);
    return os;
}

std::ostream &
operator<<(std::ostream &os, const realmz::SpellClassInfo &sci) noexcept {
    sci.print(os);
    return os;
}

std::ostream&
operator<<(std::ostream& os, const realmz::VictoryPoints& vp) noexcept
{
    vp.print(os);
    return os;
}