#include <iostream>
#include <cstdint>
#include <optional>
#include <array>
#include <tuple>
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
    void print(std::ostream& os, const std::string& fieldName) const noexcept {
       os << fieldName << ": (" << _min << ", " << _max << ", " << _adjustment << ")" << std::endl;
    }
    void print (std::ostream& os) const noexcept {
        print(os, "");
    }
private:
    int _min = 0;
    int _max = 0;
    int _adjustment = 0;

};
class SpecialAbility {
public:
    SpecialAbility() = default;
    constexpr SpecialAbility(int initial, int levelUp) : _initial(initial), _levelUp(levelUp) { }
    ~SpecialAbility() = default;
    constexpr auto getInitial() const noexcept { return _initial; }
    constexpr auto getLevelUp() const noexcept { return _levelUp; }
    void setInitial(int value) noexcept { _initial = value; }
    void setLevelUp(int value) noexcept { _levelUp = value; }
    void print(std::ostream& os, const std::string& name) const noexcept {
        os << name << ": (" << _initial << ", " << _levelUp << ")" << std::endl;
    }
    void print(std::ostream& os) const noexcept {
        print(os, "");
    }
private:
    int _initial = 0;
    int _levelUp = 0;
};
using DataBuffer = std::array<int16_t, 576/2>;
struct SpecialAbilities {
    SpecialAbility _sneakAttack;
    SpecialAbility _majorWound;
    SpecialAbility _detectSecret;
    SpecialAbility _acrobaticAct;
    SpecialAbility _detectTrap;
    SpecialAbility _disableTrap;
    SpecialAbility _forceLock;
    SpecialAbility _pickLock;
    SpecialAbility _turnUndead;
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
    void print(std::ostream& os) {
        os << "{" << std::endl;
#define X(field) _ ## field . print(os, #field )
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
        os << "}" << std::endl;
    }
};
struct DRVAdjustments {
    int _charm;
    int _heat;
    int _cold;
    int _electric;
    int _chemical;
    int _mental;
    int _magical;
    DRVAdjustments(const DataBuffer& buf) : _charm(buf[28]), _heat(buf[29]), _cold(buf[30]), _electric(buf[31]), _chemical(buf[32]), _mental(buf[33]), _magical(buf[34]) { }
    void print(std::ostream& os) {
        os << "{" << std::endl;
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
        os << "}" << std::endl;
    }
};
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
        _brawn.print(out, "Brawn");
        _knowledge.print(out, "Knowledge");
        _judgment.print(out, "Judgment");
        _agility.print(out, "Agility");
        _vitality.print(out, "Vitality");
        _luck.print(out, "Luck");
    }
};
class SpellClassInfo
{
public:
    constexpr SpellClassInfo(bool enabled, int startingLevel, int maxLevelSpells) : _enabled(enabled), _startingLevel(startingLevel), _maxLevelSpells(maxLevelSpells) { }
    constexpr auto isEnabled() const noexcept { return _enabled; }
    constexpr auto getStartingLevel() const noexcept { return _startingLevel; }
    constexpr auto getMaxLevelSpells() const noexcept { return _maxLevelSpells; }
    void print(std::ostream& out, const std::string& targetClass) const noexcept {
        out << targetClass << ": (" << std::boolalpha << _enabled << ", " << std::dec << _startingLevel << ", " << _maxLevelSpells << ")" << std::endl;
    }
private:
    bool _enabled = false;
    int _startingLevel = 0;
    int _maxLevelSpells = 0;
};
struct SpellCastingAbilities
{
public:
    SpellCastingAbilities(const DataBuffer & buf) :
    _sorcerer(buf[42], buf[43], buf[44]),
    _priest(buf[45], buf[46], buf[47]),
    _enchanter(buf[48], buf[49], buf[50]) {

    }
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
        _sorcerer.print(out, "Sorcerer");
        _priest.print(out, "Priest");
        _enchanter.print(out, "Enchanter");
    }
private:
    SpellClassInfo _sorcerer;
    SpellClassInfo _priest;
    SpellClassInfo _enchanter;
};
struct Caste {
    Caste(const DataBuffer& buffer);
    SpecialAbilities _initial;
    DRVAdjustments _drvs;
    Attributes _attributes;
    SpellCastingAbilities _spellCasting;

    void print(std::ostream& os);
};

constexpr int16_t make(uint8_t first, uint8_t second) noexcept {
    return (static_cast<int16_t>(first) << 8) | (static_cast<int16_t>(second));
}

void
Caste::print(std::ostream &os) {
    os << "{" << std::endl;
    _initial.print(os);
    _drvs.print(os);
    _attributes.print(os);
    _spellCasting.print(os);
    os << "}" << std::endl;

}

Caste::Caste(const DataBuffer &buffer) : _initial(buffer), _drvs(buffer), _attributes(buffer), _spellCasting(buffer) { }


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
    target.print(output);
    output << std::endl;
    return true;
}
int main() {
    while (readOne(std::cin, std::cout)) {
        std::cout << std::endl
                  << std::endl;
    }
    return 0;
}
