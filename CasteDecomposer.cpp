#include <iostream>
#include <cstdint>
#include <optional>
#include <array>
#include "BinaryManipulation.h"

std::optional <Caste>
readOne(std::istream &input, std::ostream &output) noexcept {
    std::array<int16_t, 576 / 2> buf;
    input.read((char *) buf.data(), 576);
    if (input.gcount() != 576) {
        return std::nullopt;
    }
    auto swap = [](int16_t value) noexcept {
        auto lower = value & 0xFF;
        auto upper = (value >> 8) & 0xFF;
        return ((lower << 8) | upper);
    };
    // swap all of the shorts to be correctly described
    for (int i = 0; i < (576 / 2); ++i) {
        buf[i] = swap(buf[i]);
    }
    return Caste(buf);
}
int main() {
    int index = 0;
    while (true) {
        if (auto result = readOne(std::cin, std::cout); result) {
            std::cout << "Caste: " << static_cast<CasteKind>(index) << std::endl;
            std::cout << *result << std::endl << std::endl << std::endl;
            ++index;
        } else {
            break;
        }
    }
    return 0;
}
