//
// Created by jwscoggins on 10/4/20.
//
#include "Character.h"
#include <iostream>
#include <filesystem>
int
main(int argc, char* argv[]) {
    if (argc == 1) {
        std::cerr << argv[0] << ": [file]" << std::endl;
        return 1;
    }
    std::string tmp(argv[1]);
    std::filesystem::path file(tmp);
    std::cout << file << std::endl;
    return 0;
}
