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
struct Caste {
    Caste(const DataBuffer& buffer);
    SpecialAbilities _initial;
    DRVAdjustments _drvs;

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
    os << "}" << std::endl;

}

Caste::Caste(const DataBuffer &buffer) : _initial(buffer), _drvs(buffer) { }


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
