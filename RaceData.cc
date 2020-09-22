//
// Created by jwscoggins on 9/20/20.
//

#include "RaceData.h"

namespace realmz {
    Hatred::Hatred(const RaceDataBuffer &buffer) :
    _hitMagicUsing(buffer[0]), _hitUndead(buffer[1]), _hitDemonic(buffer[2]),
    _hitReptilian(buffer[3]), _hitVeryEvil(buffer[4]), _hitIntelligent(buffer[5]),
    _hitGiantSize(buffer[6]), _hitNonHumanoid(buffer[7]) { }

    RaceData::RaceData(const RaceDataBuffer &buf) :
    _hatred(buf),
    _specialAbilities(buf),
    _drvs(buf),
    _attributes(buf),
    _unused1(buf[96]),
    _unused2(buf[97]),
    _baseMovementPoints(buf[98]),
    _magicResistance(buf[99]),
    _twoHandedAdjustment(buf[100]),
    _missileWeaponAdjust(buf[101]),
    _attacksPerRound(buf[102]),
    _maxAttacksPerRound(buf[103])
    {
        for (int i = 48, j = 0; i < 48 + 8; ++i, ++j) {
            _unused0[j] = buf[i];
        }
        for (int i = 56, j = 0; i < 96; ++i, ++j) {
            _conditions[j] = buf[i];
        }
        for (int i = 104, j = 0; i < 119; ++i, j+=2) {
            // its two bytes per entry
            _flags[j] = buf[i] & 0xFF;
            _flags[j+1] = (buf[i] >> 8) & 0xFF;
        }
        for (int i = 119,j = 0; i < 129; i+=2, ++j) {
            auto from = buf[i];
            auto to = buf[i+1];
            _ageRanges[j] = {from, to};
        }
    }
}