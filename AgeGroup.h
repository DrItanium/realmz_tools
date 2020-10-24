//
// Created by jwscoggins on 10/20/20.
//

#ifndef REALMZ_TOOLS_AGEGROUP_H
#define REALMZ_TOOLS_AGEGROUP_H
#include <iostream>
namespace realmz {
    enum class AgeGroup {
        None = 0,
        Youth = 1,
        Young,
        Prime,
        Adult,
        Senior,
    };
}
std::ostream &operator<<(std::ostream &os, realmz::AgeGroup group) noexcept;
#endif //REALMZ_TOOLS_AGEGROUP_H
