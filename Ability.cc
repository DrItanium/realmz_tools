//
// Created by jwscoggins on 9/20/20.
//

#include "Caste.h"
#include "Ability.h"
namespace realmz {
    void
    Ability::print(std::ostream &os) const noexcept {
        os << "(" << _initial << ", " << _levelUp << ")";
    }
} // end namespace realmz

std::ostream&
operator<<(std::ostream &os, const realmz::Ability &sa) noexcept {
    sa.print(os);
    return os;
}
