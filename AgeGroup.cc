//
// Created by jwscoggins on 10/20/20.
//

#include "AgeGroup1.h"
#include "Attribute.h"
#include "Attributes.h"
#include "DRVAdjustments.h"
#include "SpecialAbilities.h"
#include "Caste.h"
#include <fstream>
#include <optional>
#include <map>
#include "AgeGroup.h"
std::ostream &operator<<(std::ostream &os, realmz::AgeGroup group) noexcept {
    switch (group) {
        case realmz::AgeGroup::Youth:
            os << "Youth";
            break;
        case realmz::AgeGroup::Young:
            os << "Young";
            break;
        case realmz::AgeGroup::Prime:
            os << "Prime";
            break;
        case realmz::AgeGroup::Adult:
            os << "Adult";
            break;
        case realmz::AgeGroup::Senior:
            os << "Senior";
            break;
        default:
            os << "UNKNOWN_AGE_GROUP(" << static_cast<int>(group) << ")!";
            break;
    }
    return os;
}