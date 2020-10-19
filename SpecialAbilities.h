//
// Created by jwscoggins on 9/20/20.
//

#ifndef REALMZ_TOOLS_SPECIALABILITIES_H
#define REALMZ_TOOLS_SPECIALABILITIES_H
#include <cstdint>
#include <optional>
#include <array>
#include <vector>
#include "Ability.h"
#include "CasteDataBuffer.h"
#include "RaceDataBuffer.h"
namespace realmz {

class SpecialAbilities {
public:
    SpecialAbilities(const realmz::CasteDataBuffer& buf);
    SpecialAbilities(const realmz::RaceDataBuffer& buf);
    void print(std::ostream& os) const noexcept;
    [[nodiscard]] constexpr const Ability& getSneakAttack() const noexcept { return _sneakAttack; }
    [[nodiscard]] constexpr const Ability& getMajorWound() const noexcept { return _majorWound; }
    [[nodiscard]] constexpr const Ability& getDetectSecret() const noexcept { return _detectSecret; }
    [[nodiscard]] constexpr const Ability& getAcrobaticAct() const noexcept { return _acrobaticAct; }
    [[nodiscard]] constexpr const Ability& getDetectTrap() const noexcept { return _detectTrap; }
    [[nodiscard]] constexpr const Ability& getDisableTrap() const noexcept { return _disableTrap; }
    [[nodiscard]] constexpr const Ability& getForceLock() const noexcept { return _forceLock; }
    [[nodiscard]] constexpr const Ability& getPickLock() const noexcept { return _pickLock; }
    [[nodiscard]] constexpr const Ability& getTurnUndead() const noexcept { return _turnUndead; }
private:
    realmz::Ability _sneakAttack;
    realmz::Ability _majorWound;
    realmz::Ability _detectSecret;
    realmz::Ability _acrobaticAct;
    realmz::Ability _detectTrap;
    realmz::Ability _disableTrap;
    realmz::Ability _forceLock;
    realmz::Ability _pickLock;
    realmz::Ability _turnUndead;


};

}
std::ostream &operator<<(std::ostream &os, const realmz::SpecialAbilities &sa) noexcept;
#endif //REALMZ_TOOLS_SPECIALABILITIES_H
