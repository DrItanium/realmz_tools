//
// Created by jwscoggins on 10/17/20.
//

#ifndef REALMZ_TOOLS_SPELL_H
#define REALMZ_TOOLS_SPELL_H
#include <cstdint>
#include <array>
#include "Utilities.h"
#include "BinaryManipulation.h"
namespace realmz {
    class Spell {
    public:
        static constexpr auto ClassicStructureSize = 30;
        using ClassicDataBuffer = std::array<int16_t, ClassicStructureSize/2>;
    public:
        constexpr explicit Spell(const ClassicDataBuffer& buf) :
        _id(buf[0]),
        _unknown0({
            buf[1],
            buf[2],
            buf[3],
            buf[4],
            buf[5],
            buf[6],
            buf[7],
            buf[8],
            buf[9],
            buf[10],
            buf[11]
        }),
        _unknown1(upperHalf(buf[12])),
        _spellCastingKind(buf[12]),
        _unknown2(buf[13]),
        _unknown3(buf[14]) {}
        [[nodiscard]] constexpr auto getId() const noexcept { return _id; }
        [[nodiscard]] constexpr auto getSpellCastingKind() const noexcept { return _spellCastingKind; }

        void setId(uint16_t id) noexcept { _id = id; }
        void setSpellCastingKind(uint8_t spellCastingKind) noexcept { _spellCastingKind = spellCastingKind; }
    private:
        uint16_t _id = 0;
        std::array<int16_t, 11> _unknown0 = { 0 };
        uint8_t _unknown1 = 0;
        uint8_t _spellCastingKind = 0;
        int16_t _unknown2 = 0;
        int16_t _unknown3 = 0;

    };
} // end namespace realmz

#endif //REALMZ_TOOLS_SPELL_H
