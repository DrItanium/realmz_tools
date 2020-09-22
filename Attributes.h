//
// Created by jwscoggins on 9/21/20.
//

#ifndef REALMZ_TOOLS_ATTRIBUTES_H
#define REALMZ_TOOLS_ATTRIBUTES_H
#include <iostream>
#include "CasteDataBuffer.h"
#include "RaceDataBuffer.h"
#include "Attribute.h"

namespace realmz {

    struct Attributes {
    public:
        Attribute _brawn;
        Attribute _knowledge;
        Attribute _judgment;
        Attribute _agility;
        Attribute _vitality;
        Attribute _luck;
        Attributes(const realmz::CasteDataBuffer &buf);
        Attributes(const realmz::RaceDataBuffer &buf);
        void print(std::ostream &out) const noexcept;
    };
} // end namespace realmz
std::ostream &operator<<(std::ostream &os, const realmz::Attributes &attrib) noexcept;

#endif //REALMZ_TOOLS_ATTRIBUTES_H
