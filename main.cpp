#include <iostream>
#include <cstdint>
#include <optional>
#include <array>

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
};

std::ostream& operator<<(std::ostream& os, CasteKind ck) noexcept {
    switch (ck) {
#define X(field, str) case CasteKind:: field : os << str; break
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
class CharacterAttribute {
public:
    CharacterAttribute() = default;
    constexpr CharacterAttribute(int min, int max, int adjustment) : _min(min), _max(max), _adjustment(adjustment) {}
    void setMin(int value) noexcept { _min = value; }
    void setMax(int value) noexcept { _max = value; }
    void setAdjustment(int value) noexcept { _adjustment = value; }
    constexpr auto getMin() const noexcept { return _min; }
    constexpr auto getMax() const noexcept { return _max; }
    constexpr auto getAdjustment() const noexcept { return _adjustment; }
    void print(std::ostream& os) const noexcept {
       os << "(" << _min << ", " << _max << ", " << _adjustment << ")";
    }
private:
    int _min = 0;
    int _max = 0;
    int _adjustment = 0;

};
std::ostream& operator<<(std::ostream& os, const CharacterAttribute& ca) noexcept {
    ca.print(os);
    return os;
}
class Ability {
public:
    Ability() = default;
    constexpr Ability(int initial, int levelUp) : _initial(initial), _levelUp(levelUp) { }
    ~Ability() = default;
    constexpr auto getInitial() const noexcept { return _initial; }
    constexpr auto getLevelUp() const noexcept { return _levelUp; }
    void setInitial(int value) noexcept { _initial = value; }
    void setLevelUp(int value) noexcept { _levelUp = value; }
    void print(std::ostream& os) const noexcept { os << "(" << _initial << ", " << _levelUp << ")"; }
private:
    int _initial = 0;
    int _levelUp = 0;
};

std::ostream& operator<<(std::ostream& os, const Ability& sa) noexcept {
    sa.print(os);
    return os;
}
using DataBuffer = std::array<int16_t, 576/2>;
struct SpecialAbilities {
    Ability _sneakAttack;
    Ability _majorWound;
    Ability _detectSecret;
    Ability _acrobaticAct;
    Ability _detectTrap;
    Ability _disableTrap;
    Ability _forceLock;
    Ability _pickLock;
    Ability _turnUndead;
    SpecialAbilities(const DataBuffer& buf) :
            _sneakAttack(buf[0], buf[14]),
            _majorWound(buf[3], buf[14+3]),
            _detectSecret(buf[4], buf[14+4]),
            _acrobaticAct(buf[5], buf[14+5]),
            _detectTrap(buf[6], buf[14+6]),
            _disableTrap(buf[7], buf[14+7]),
            _forceLock(buf[9], buf[14+9]),
            _pickLock(buf[11], buf[14+11]),
            _turnUndead(buf[13], buf[14+13]) {
    }
    void print(std::ostream& os) const noexcept {
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
};
std::ostream& operator<<(std::ostream& os, const SpecialAbilities& sa) noexcept {
    sa.print(os);
    return os;
}
struct DRVAdjustments {
    int _charm;
    int _heat;
    int _cold;
    int _electric;
    int _chemical;
    int _mental;
    int _magical;
    DRVAdjustments(const DataBuffer& buf) : _charm(buf[28]), _heat(buf[29]), _cold(buf[30]), _electric(buf[31]), _chemical(buf[32]), _mental(buf[33]), _magical(buf[34]) { }
    void print(std::ostream& os) const noexcept {
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
};
std::ostream& operator<<(std::ostream& os, const DRVAdjustments& drv) noexcept {
    drv.print(os);
    return os;
}
struct Attributes {
public:
    CharacterAttribute _brawn;
    CharacterAttribute _knowledge;
    CharacterAttribute _judgment;
    CharacterAttribute _agility;
    CharacterAttribute _vitality;
    CharacterAttribute _luck;
    Attributes(const DataBuffer& buf) :
    _brawn(buf[54], buf[55], buf[36]),
    _knowledge(buf[56], buf[57], buf[37]),
    _judgment(buf[58], buf[59], buf[38]),
    _agility(buf[60], buf[61], buf[39]),
    _vitality(buf[62], buf[63], buf[40]),
    _luck(buf[64],buf[65],buf[41]) {

    }
    void print(std::ostream& out) const noexcept {
        out << "Brawn: " << _brawn << std::endl;
        out << "Knowledge: " << _knowledge << std::endl;
        out << "Judgment: " << _judgment << std::endl;
        out << "Agility: " << _agility << std::endl;
        out << "Vitality: " << _vitality << std::endl;
        out << "Luck: " << _luck<< std::endl;
    }
};

std::ostream& operator<<(std::ostream& os, const Attributes& attrib) noexcept {
    attrib.print(os);
    return os;
}
class SpellClassInfo
{
public:
    constexpr SpellClassInfo(bool enabled, int startingLevel, int maxLevelSpells) : _enabled(enabled), _startingLevel(startingLevel), _maxLevelSpells(maxLevelSpells) { }
    constexpr auto isEnabled() const noexcept { return _enabled; }
    constexpr auto getStartingLevel() const noexcept { return _startingLevel; }
    constexpr auto getMaxLevelSpells() const noexcept { return _maxLevelSpells; }
    void print(std::ostream& out) const noexcept {
        out << "(" << std::boolalpha << _enabled << ", " << std::dec << _startingLevel << ", " << _maxLevelSpells << ")";
    }
private:
    bool _enabled = false;
    int _startingLevel = 0;
    int _maxLevelSpells = 0;
};
std::ostream&
operator<<(std::ostream& os, const SpellClassInfo& sci) noexcept
{
    sci.print(os) ;
    return os;
}
struct SpellCastingAbilities
{
public:
    SpellCastingAbilities(const DataBuffer & buf) :
    _sorcerer(buf[42], buf[43], buf[44]),
    _priest(buf[45], buf[46], buf[47]),
    _enchanter(buf[48], buf[49], buf[50]) { }
    const SpellClassInfo& getSorcererInfo() const noexcept { return _sorcerer; }
    const SpellClassInfo& getPriestInfo() const noexcept { return _priest; }
    const SpellClassInfo& getEnchanterInfo() const noexcept { return _enchanter; }
    constexpr bool canCastSpells() const noexcept { return _sorcerer.isEnabled() || _priest.isEnabled() || _enchanter.isEnabled(); }
    constexpr bool supportsSorcererSpellClass() const noexcept { return _sorcerer.isEnabled(); }
    constexpr bool supportsPriestSpellClass() const noexcept { return _priest.isEnabled(); }
    constexpr bool supportsEnchanterSpellClass() const noexcept { return _enchanter.isEnabled(); }
    constexpr auto getStartingLevel() const noexcept {
        if (_sorcerer.isEnabled()) {
            return _sorcerer.getStartingLevel();
        } else if (_priest.isEnabled()) {
            return _priest.getStartingLevel();
        } else if (_enchanter.isEnabled()) {
            return _enchanter.getStartingLevel();
        } else {
            return -1;
        }
    }
    constexpr auto getMaxLevelSpells() const noexcept {
        if (_sorcerer.isEnabled()) {
            return _sorcerer.getMaxLevelSpells();
        } else if (_priest.isEnabled()) {
            return _priest.getMaxLevelSpells();
        } else if (_enchanter.isEnabled()) {
            return _enchanter.getMaxLevelSpells();
        } else {
            return -1;
        }
    }
    void print(std::ostream& out) const noexcept {
        out << "Sorcerer: " << _sorcerer << std::endl;
        out << "Priest: " << _priest << std::endl;
        out << "Enchanter: " << _enchanter << std::endl;
    }
private:
    SpellClassInfo _sorcerer;
    SpellClassInfo _priest;
    SpellClassInfo _enchanter;
};
std::ostream& operator<<(std::ostream& os, const SpellCastingAbilities& sci) noexcept {
    sci.print(os);
    return os;
}
enum class AgeGroup {
    None = 0,
    Young = 1,
    Youth,
    Prime,
    Adult,
    Senior,
};
std::ostream& operator<<(std::ostream& os, AgeGroup group) noexcept {
    switch (group) {
        case AgeGroup::Youth:
            os << "Youth";
            break;
        case AgeGroup::Young:
            os << "Young";
            break;
        case AgeGroup::Prime:
            os << "Prime";
            break;
        case AgeGroup::Adult:
            os << "Adult";
            break;
        case AgeGroup::Senior:
            os << "Senior";
            break;
        default:
            os << "UNKNOWN_AGE_GROUP(" << static_cast<int>(group) << ")!";
            break;
    }
    return os;
}
class Caste {
public:
    Caste(const DataBuffer& buffer);
    void print(std::ostream& os) const noexcept;
private:
    SpecialAbilities _initial;
    DRVAdjustments _drvs;
    Attributes _attributes;
    SpellCastingAbilities _spellCasting;
    bool _canUseMissileWeapons = false;
    bool _getsMissileBonusDamage = false;
    Ability _stamina;
    Ability _dodgeMissile;
    Ability _meleeAttack;
    Ability _missileAttack;
    Ability _handToHand;
    int _creatorCodeId = 0;
    AgeGroup _startingAgeGroup = AgeGroup::None;
};

constexpr int16_t make(uint8_t first, uint8_t second) noexcept {
    return (static_cast<int16_t>(first) << 8) | (static_cast<int16_t>(second));
}

std::ostream& operator<<(std::ostream& os, const Caste& caste) noexcept {
    caste.print(os);
    return os;
}


void
Caste::print(std::ostream &os) const noexcept {
    os << _initial << _drvs << _attributes << _spellCasting;
    os << "Can Use Missile Weapons: " << std::boolalpha << _canUseMissileWeapons << std::endl;
    os << "Gets Missile Bonus Damage: " << std::boolalpha << _getsMissileBonusDamage << std::endl;
    os << "Stamina: " << _stamina << std::endl;
    os << "Dodge Missile: " << _dodgeMissile << std::endl;
    os << "Melee Attack: " << _meleeAttack << std::endl;
    os << "Missile Attack: " << _missileAttack << std::endl;
    os << "Hand To Hand: " << _handToHand << std::endl;
    os << "Creator Code Id?: " << _creatorCodeId << std::endl;
    os << "Starting Age Group: " << _startingAgeGroup << std::endl;
}

Caste::Caste(const DataBuffer &buffer) :
_initial(buffer),
_drvs(buffer),
_attributes(buffer),
_spellCasting(buffer),
_canUseMissileWeapons(buffer[106]),
_getsMissileBonusDamage(buffer[107]),
_stamina(buffer[108], buffer[109]),
// skip buffer 110 and 111 for now, unsure what it is for
_dodgeMissile(buffer[112], buffer[113]),
_meleeAttack(buffer[114], buffer[115]),
_missileAttack(buffer[116], buffer[117]),
_handToHand(buffer[118], buffer[119]),
_creatorCodeId(buffer[124]),
_startingAgeGroup(static_cast<AgeGroup>(buffer[125]))
{ }


bool
readOne(std::istream& input, std::ostream& output) noexcept {
    std::array<int16_t, 576 / 2> buf;
    input.read((char*)buf.data(), 576);
    if (input.gcount() != 576) {
        return false;
    }
    auto swap = [](int16_t value) noexcept {
       auto lower = value & 0xFF;
       auto upper = (value >> 8) & 0xFF;
       return ((lower << 8) | upper);
    };
    // swap all of the shorts to be correctly described
    for (int i = 0; i < (576/2); ++i) {
        buf[i] = swap(buf[i]);
    }
    Caste target(buf);
    output << target << std::endl;
    return true;
}
int main() {
    bool invoke = true;
    int index = 0;
    while (invoke) {
        std::cout << "Caste: " << static_cast<CasteKind>(index) << std::endl;
        invoke = readOne(std::cin, std::cout);
        std::cout << std::endl
                  << std::endl;
        ++index;
    }
    return 0;
}
