//
// Created by jwscoggins on 10/31/20.
//

#ifndef REALMZ_TOOLS_APPLICATIONUTILITIES_H
#define REALMZ_TOOLS_APPLICATIONUTILITIES_H
#include <filesystem>
const std::filesystem::path& getApplicationDirectory() noexcept;
const std::filesystem::path& getResourcesDirectory() noexcept;
const std::filesystem::path& getPortraitsDirectory() noexcept;
const std::filesystem::path& getTacticalsDirectory() noexcept;
const std::filesystem::path& getBinaryResourcesDir() noexcept;

#endif //REALMZ_TOOLS_APPLICATIONUTILITIES_H
