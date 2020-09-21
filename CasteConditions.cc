//
// Created by jwscoggins on 9/20/20.
//

#include "CasteConditions.h"

namespace realmz {

    CasteConditions::CasteConditions(const CasteDataBuffer & buf) {
        constexpr auto startPosition = 66;
        constexpr auto endPosition = startPosition + 40;
        for (int i = startPosition, j = 0; i < endPosition; ++i, ++j) {
            _contents[j] = buf[i];
        }
    }

    void
    CasteConditions::print(std::ostream& os) const noexcept {
        os << "Conditions {" << std::endl;
        for (const auto& level : _contents) {
            if (level != 0) {
                os << "\tAt Level: " << std::dec << level << std::endl;
            }
        }
        os << "}" << std::endl;
    }

} // end namespace realmz
std::ostream&
operator<<(std::ostream& os, const realmz::CasteConditions& conditions) noexcept {
    conditions.print(os);
    return os;
}
