//
// Created by jwscoggins on 9/21/20.
//

#include "Attributes.h"

namespace realmz {

    void
    Attributes::print(std::ostream &out) const noexcept
    {
        out << "Brawn: " << _brawn << std::endl;
        out << "Knowledge: " << _knowledge << std::endl;
        out << "Judgment: " << _judgment << std::endl;
        out << "Agility: " << _agility << std::endl;
        out << "Vitality: " << _vitality << std::endl;
        out << "Luck: " << _luck << std::endl;
    }

    Attributes::Attributes(const CasteDataBuffer &buf) :
            _brawn(buf[54], buf[55], buf[36]),
            _knowledge(buf[56], buf[57], buf[37]),
            _judgment(buf[58], buf[59], buf[38]),
            _agility(buf[60], buf[61], buf[39]),
            _vitality(buf[62], buf[63], buf[40]),
            _luck(buf[64], buf[65], buf[41]) {

    }
}

std::ostream&
operator<<(std::ostream &os, const realmz::Attributes &ca) noexcept {
    ca.print(os);
    return os;
}
