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

struct SpecialAbilities {
    realmz::Ability _sneakAttack;
    realmz::Ability _majorWound;
    realmz::Ability _detectSecret;
    realmz::Ability _acrobaticAct;
    realmz::Ability _detectTrap;
    realmz::Ability _disableTrap;
    realmz::Ability _forceLock;
    realmz::Ability _pickLock;
    realmz::Ability _turnUndead;
    SpecialAbilities(const realmz::CasteDataBuffer& buf);
    SpecialAbilities(const realmz::RaceDataBuffer& buf);
    void print(std::ostream& os) const noexcept;


};

}
std::ostream &operator<<(std::ostream &os, const realmz::SpecialAbilities &sa) noexcept;
#endif //REALMZ_TOOLS_SPECIALABILITIES_H
