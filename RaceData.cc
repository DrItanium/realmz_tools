//
// Created by jwscoggins on 9/20/20.
//

#include "RaceData.h"

namespace realmz {
    Hatred::Hatred(const RaceDataBuffer &buffer) :
    _hitMagicUsing(buffer[0]), _hitUndead(buffer[1]), _hitDemonic(buffer[2]),
    _hitReptilian(buffer[3]), _hitVeryEvil(buffer[4]), _hitIntelligent(buffer[5]),
    _hitGiantSize(buffer[6]), _hitNonHumanoid(buffer[7]) { }
}