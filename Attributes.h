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

    class Attributes {
    public:
        explicit Attributes(const realmz::CasteDataBuffer &buf);
        explicit Attributes(const realmz::RaceDataBuffer &buf);
        void print(std::ostream &out) const noexcept;
        [[nodiscard]] const Attribute& getBrawn() const noexcept { return _brawn; }
        [[nodiscard]] const Attribute& getKnowledge() const noexcept { return _knowledge; }
        [[nodiscard]] const Attribute& getJudgment() const noexcept { return _judgment; }
        [[nodiscard]] const Attribute& getAgility() const noexcept { return _agility; }
        [[nodiscard]] const Attribute& getVitality() const noexcept { return _vitality; }
        [[nodiscard]] const Attribute& getLuck() const noexcept { return _luck; }
    private:
        Attribute _brawn;
        Attribute _knowledge;
        Attribute _judgment;
        Attribute _agility;
        Attribute _vitality;
        Attribute _luck;
    };
} // end namespace realmz
std::ostream &operator<<(std::ostream &os, const realmz::Attributes &attrib) noexcept;

#endif //REALMZ_TOOLS_ATTRIBUTES_H
