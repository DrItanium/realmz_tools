#include <iostream>
#include <cstdint>
#include <optional>
#include <array>
#include <tuple>
class SpecialAbility {
public:
    SpecialAbility() = default;
    constexpr SpecialAbility(int initial, int levelUp) : _initial(initial), _levelUp(levelUp) { }
    ~SpecialAbility() = default;
    constexpr auto getInitial() const noexcept { return _initial; }
    constexpr auto getLevelUp() const noexcept { return _levelUp; }
    void setInitial(int value) noexcept { _initial = value; }
    void setLevelUp(int value) noexcept { _levelUp = value; }
    void print(const std::string& name, std::ostream& os) const noexcept {
        os << name << ": (" << _initial << ", " << _levelUp << ")" << std::endl;
    }
    void print(std::ostream& os) const noexcept {
        print("", os);
    }
private:
    int _initial = 0;
    int _levelUp = 0;
};
struct Caste {
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

        void print(std::ostream& os) {
            os << "{" << std::endl;
#define X(field) _ ## field . print( #field , os)
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
    struct CasteDRVAdjustments {
        int _charm;
        int _heat;
        int _cold;
        int _electric;
        int _chemical;
        int _mental;
        int _magical;

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
    SpecialAbilities _initial;
    CasteDRVAdjustments _adjustmentForCaste;

    void print(std::ostream& os);
};

constexpr int16_t make(uint8_t first, uint8_t second) noexcept {
    return (static_cast<int16_t>(first) << 8) | (static_cast<int16_t>(second));
}
int16_t make(std::istream& in) noexcept {
    auto f = in.get();
    auto s = in.get();
    return make(f, s);
}

void
Caste::print(std::ostream &os) {
    os << "{" << std::endl;
    _initial.print(os);
    _adjustmentForCaste.print(os);
    os << "}" << std::endl;

}

bool
readOne(std::istream& input, std::ostream& output) noexcept {
    std::array<char, 576> buf;
    input.read(buf.data(), 576);
    if (input.gcount() != 576) {
        return false;
    }
    if (auto target = makeCaste(buf.cbegin(), buf.cend()); target) {
        target->print(output);
        output << std::endl;
        return true;
    } else {
        return false;
    }
}
int main() {
    while (readOne(std::cin, std::cout)) {
        std::cout << std::endl
                  << std::endl;
    }
    return 0;
}
