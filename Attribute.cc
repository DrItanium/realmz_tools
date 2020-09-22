//
// Created by jwscoggins on 9/21/20.
//

#include "Attribute.h"

namespace realmz {
    void
    Attribute::print(std::ostream &os) const noexcept {
        os << "(" << _min << ", " << _max << ", " << _adjustment << ")";
    }
}

std::ostream&
operator<<(std::ostream &os, const realmz::Attribute &ca) noexcept {
    ca.print(os);
    return os;
}
