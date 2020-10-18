//
// Created by jwscoggins on 9/20/20.
//
#include <map>
#include <optional>
#include <fstream>
#include "Caste.h"
#include "SpecialAbilities.h"
#include "DRVAdjustments.h"
#include "Attributes.h"
#include "Attribute.h"

namespace realmz {
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
            _victoryPointsAtLevel(buffer),
            _initialGoldAmount(buffer[384 / 2]) // used to be initialItemsLength
    {
        constexpr auto itemsStartPos = 386/2;
        constexpr auto itemsEndPos = itemsStartPos + 20;
        for (int i = itemsStartPos; i < itemsEndPos; ++i) {
            if (auto target = buffer[i]; target != 0) {
                _initialItems.emplace_back(target);
            }
        }
        // need to pull in a 64-bit number
        constexpr auto AllowedBitsPos = 436/2;
        // this was originally two 32-bit numbers so it may be necessary to do two sets of swaps
        // I will need to migrate this to a non binary quantity in a knowledge base as this is a nightmare to make sure we are
        // reading it correctly!
        auto highest = static_cast<int64_t>(buffer[AllowedBitsPos]);
        auto higher = static_cast<int64_t>(buffer[AllowedBitsPos + 1]);
        auto lower = static_cast<int64_t>(buffer[AllowedBitsPos + 2]);
        auto lowest = static_cast<int64_t>(buffer[AllowedBitsPos + 3]);
        _allowedBits = ((highest << 48) & 0xFFFF'0000'0000'0000) |
                       ((higher << 32) & 0x0000'FFFF'0000'0000) |
                       ((lower << 16) & 0x0000'0000'FFFF'0000) |
                       (lowest & 0x0000'0000'0000'FFFF);
    }

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
        os << "Initial Gold: " << std::dec << _initialGoldAmount << std::endl;
        os << "Initial Items {" << std::endl;
        int pos = 1;
        for (const auto itemIndex : _initialItems) {
            os << "\t" << std::dec << pos << ": " << std::dec << itemIndex << std::endl;
            ++pos;
        }
        os << "}" << std::endl;
        os << "Allowed Bits: " << std::hex << _allowedBits << std::endl;
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
    VictoryPoints::print(std::ostream &os) const noexcept {
        os << "Victory Points @ Level {" << std::endl;
        int index = 1;
        for (const auto& value : _contents) {
            os << "\t" << std::dec << index << ": " <<  std::dec << value << std::endl;
            ++index;
        }
        os << "}" << std::endl;
    }
    VictoryPoints::VictoryPoints(const CasteDataBuffer &buf) {
        constexpr auto startPosition = 264 / 2;
        constexpr auto endPosition = startPosition + (30 * 2); // these are int32_t's
        for (int i = startPosition; i < endPosition; i+=2) {
            // eliminate sign extension by making it unsigned
            auto upper = static_cast<int32_t>(buf[i]) & 0xFFFF;
            auto lower = static_cast<int32_t>(buf[i + 1]) & 0xFFFF;
            auto result = lower | ((upper << 16) & 0xFFFF0000);
            _contents.emplace_back(result); // we need to make sure that these are marked as negative when stored in a character
        }
    }
    namespace {
        bool loadedRaceData = false;
        std::filesystem::path casteDataLocation;
        std::map<CasteKind, Caste> registeredCasteData;
        void
        loadCasteData() {
            if (loadedRaceData) {
                return;
            }
            auto readOne = [](std::istream& input) -> std::optional<Caste> {
                std::array<int16_t, 576 / 2> buf;
                input.read((char *) buf.data(), 576);
                if (input.gcount() != 576) {
                    return std::nullopt;
                }
                auto swap = [](int16_t value) noexcept {
                    auto lower = value & 0xFF;
                    auto upper = (value >> 8) & 0xFF;
                    return ((lower << 8) | upper);
                };
                // swap all of the shorts to be correctly described
                for (int i = 0; i < (576 / 2); ++i) {
                    buf[i] = swap(buf[i]);
                }
                return {buf};
            };
            std::ifstream casteDataFile(casteDataLocation);
            if (!casteDataFile.is_open()) {
                throw "Couldn't open caste data file";
            }
            for (int curr = static_cast<int>(CasteKind::Fighter);  curr != static_cast<int>(CasteKind::Done); ++curr) {
                auto theCaste = static_cast<CasteKind>(curr);
                if (auto result = readOne(casteDataFile); result) {
                    registeredCasteData.emplace(theCaste, *result);
                } else {
                    throw "Couldn't load all entries";
                }
            }
            casteDataFile.close();
            loadedRaceData = true;
        }
    }

    void setCasteDataLocation(const std::filesystem::path& path) noexcept {
        casteDataLocation = path;
        loadedRaceData = false;
    }
    bool casteDataLocationSet() noexcept {
        return !casteDataLocation.empty();
    }

    const Caste&
    loadCaste(CasteKind ck) {
        loadCasteData();
        if (casteDataLocation.empty()) {
            throw "Caste data not loaded";
        } else {
            if (auto pos = registeredCasteData.find(ck); pos != registeredCasteData.end()) {
                return pos->second;
            } else {
                throw "Unknown caste kind!";
            }
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
