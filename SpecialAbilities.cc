//
// Created by jwscoggins on 9/20/20.
//

#include "SpecialAbilities.h"
#include "Ability.h"
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
    SpecialAbilities::SpecialAbilities(const RaceDataBuffer &buf) :
    _sneakAttack(buf[8], 0), _majorWound(buf[11], 0),
    _detectSecret(buf[12], 0), _acrobaticAct(buf[13], 0),
    _detectTrap(buf[14], 0), _disableTrap(buf[15], 0),
    _forceLock(buf[17], 0), _pickLock(buf[19], 0),
    _turnUndead(buf[21], 0)
    {

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
} // end namespace realmz
std::ostream&
operator<<(std::ostream &os, const realmz::SpecialAbilities &sa) noexcept {
sa.print(os);
return os;
}
