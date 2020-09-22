//
// Created by jwscoggins on 9/21/20.
//

#ifndef REALMZ_TOOLS_ATTRIBUTE_H
#define REALMZ_TOOLS_ATTRIBUTE_H
#include <iostream>

namespace realmz {

    class Attribute {
    public:
        constexpr Attribute(int min, int max, int adjustment) : _min(min), _max(max), _adjustment(adjustment) {}
        constexpr auto getMin() const noexcept { return _min; }
        constexpr auto getMax() const noexcept { return _max; }
        constexpr auto getAdjustment() const noexcept { return _adjustment; }
        void print(std::ostream& os) const noexcept;
    private:
        int _min = 3;
        int _max = 25;
        int _adjustment = 0;
    };

}
std::ostream& operator<<(std::ostream& os, const realmz::Attribute& ca) noexcept;
#endif //REALMZ_TOOLS_ATTRIBUTE_H
