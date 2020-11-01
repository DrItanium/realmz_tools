//
// Created by jwscoggins on 9/20/20.
//

#ifndef REALMZ_TOOLS_CASTECONDITIONS_H
#define REALMZ_TOOLS_CASTECONDITIONS_H
#include "CasteDataBuffer.h"
#include <iostream>
namespace realmz {
    class CharacterConditions;
    class CasteConditions {
    public:
        CasteConditions(const CasteDataBuffer &);
        void print(std::ostream&) const noexcept;
        void accept(CharacterConditions& cc) const noexcept;
    private:
        std::array<int16_t, 40> _contents = { 0 };
    };
}

std::ostream& operator<<(std::ostream& os, const realmz::CasteConditions& conditions) noexcept;

#endif //REALMZ_TOOLS_CASTECONDITIONS_H
