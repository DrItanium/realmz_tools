//
// Created by jwscoggins on 9/20/20.
//

#ifndef REALMZ_TOOLS_ABILITY_H
#define REALMZ_TOOLS_ABILITY_H
#include <iostream>
#include <cstdint>
#include <optional>
#include <array>
namespace realmz {
    class Ability {
    public:
        Ability() = default;
        constexpr Ability(int initial, int levelUp) : _initial(initial), _levelUp(levelUp) {}
        ~Ability() = default;
        constexpr auto getInitial() const noexcept { return _initial; }
        constexpr auto getLevelUp() const noexcept { return _levelUp; }
        void setInitial(int value) noexcept { _initial = value; }
        void setLevelUp(int value) noexcept { _levelUp = value; }
        void print(std::ostream &os) const noexcept;
    private:
        int _initial = 0;
        int _levelUp = 0;
    };
}
#endif //REALMZ_TOOLS_ABILITY_H
