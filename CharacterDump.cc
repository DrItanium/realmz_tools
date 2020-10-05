//
// Created by jwscoggins on 10/4/20.
//
#include "Character.h"
#include <fstream>
#include <filesystem>
int
main(int argc, char* argv[]) {
    if (argc == 1) {
        std::cerr << argv[0] << ": [file]" << std::endl;
        return 1;
    }
    std::string tmp(argv[1]);
    std::filesystem::path file(tmp);
    std::ifstream inputFile(file);
    if (!inputFile.is_open()) {
        std::cerr << "Could not open " << file << std::endl;
        return 1;
    } else {
        realmz::CharacterDataBuffer buf;
        inputFile.read((char*)buf.data(), 872);
        if (inputFile.gcount() != 872) {
            std::cerr << "File: " << file << " does not seem to be a character (too small!)" << std::endl;
            inputFile.close();
            return 1;
        }
        auto swap = [](int16_t value) noexcept {
            auto lower = value & 0xFF;
            auto upper = (value >> 8) & 0xFF;
            return ((lower << 8) | upper);
        };
        for (int i = 0; i < (872/2); ++i) {
            buf[i] = swap(buf[i]);
        }
        inputFile.close();
        realmz::Character c(buf);
        std::cout << c << std::endl;
    }

    return 0;
}
