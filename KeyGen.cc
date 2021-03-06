//
// Generate keys for all of fantasoft shipped scenarios and potentially custom scenarios later on, a different key setup is used for those
// Pulled the logic from the realmz executable itself using GHIDRA
// Created by jwscoggins on 9/13/20.
//
#include <cstdint>
#include <iostream>
#include <sstream>
#include <filesystem>
#include <array>
#include <fstream>
#include <string>
#include <vector>
constexpr uint8_t translationTable[] = {
        0x0, 0x1, 0x2, 0x3,
        0x4, 0x5, 0x6, 0x7,
        0x8, 0x9, 0xA, 0xB,
        0xC, 0xD, 0xE, 0xF,
        0x10, 0x11, 0x12, 0x13,
        0x14, 0x15, 0x16, 0x17,
        0x18, 0x19, 0x1A, 0x1B,
        0x1C, 0x1D, 0x1E, 0x1F,
        0x20, 0x21, 0x22, 0x23,
        0x24, 0x25, 0x26, 0x27,
        0x28, 0x29, 0x2A, 0x2B,
        0x2C, 0x2D, 0x2E, 0x2F,
        0x30, 0x31, 0x32, 0x33,
        0x34, 0x35, 0x36, 0x37,
        0x38, 0x39, 0x3A, 0x3B,
        0x3C, 0x3D, 0x3E, 0x3F,
        0x40, 0x61, 0x62, 0x63,
        0x64, 0x65, 0x66, 0x67,
        0x68, 0x69, 0x6A, 0x6B,
        0x6C, 0x6D, 0x6E, 0x6F,
        0x70, 0x71, 0x72, 0x73,
        0x74, 0x75, 0x76, 0x77,
        0x78, 0x79, 0x7A, 0x5B,
        0x5C, 0x5D, 0x5E, 0x5F,
        0x60, 0x61, 0x62, 0x63,
        0x64, 0x65, 0x66, 0x67,
        0x68, 0x69, 0x6A, 0x6B,
        0x6C, 0x6D, 0x6E, 0x6F,
        0x70, 0x71, 0x72, 0x73,
        0x74, 0x75, 0x76, 0x77,
        0x78, 0x79, 0x7A, 0x7B,
        0x7C, 0x7D, 0x7E, 0x7F,
        0x80, 0x81, 0x82, 0x83,
        0x84, 0x85, 0x86, 0x87,
        0x88, 0x89, 0x8A, 0x8B,
        0x8C, 0x8D, 0x8E, 0x8F,
        0x90, 0x91, 0x92, 0x93,
        0x94, 0x95, 0x96, 0x97,
        0x98, 0x99, 0x9A, 0x9B,
        0x9C, 0x9D, 0x9E, 0x9F,
        0xA0, 0xA1, 0xA2, 0xA3,
        0xA4, 0xA5, 0xA6, 0xA7,
        0xA8, 0xA9, 0xAA, 0xAB,
        0xAC, 0xAD, 0xAE, 0xAF,
        0xB0, 0xB1, 0xB2, 0xB3,
        0xB4, 0xB5, 0xB6, 0xB7,
        0xB8, 0xB9, 0xBA, 0xBB,
        0xBC, 0xBD, 0xBE, 0xBF,
        0xC0, 0xC1, 0xC2, 0xC3,
        0xC4, 0xC5, 0xC6, 0xC7,
        0xC8, 0xC9, 0xCA, 0xCB,
        0xCC, 0xCD, 0xCE, 0xCF,
        0xD0, 0xD1, 0xD2, 0xD3,
        0xD4, 0xD5, 0xD6, 0xD7,
        0xD8, 0xD9, 0xDA, 0xDB,
        0xDC, 0xDD, 0xDE, 0xDF,
        0xE0, 0xE1, 0xE2, 0xE3,
        0xE4, 0xE5, 0xE6, 0xE7,
        0xE8, 0xE9, 0xEA, 0xEB,
        0xEC, 0xED, 0xEE, 0xEF,
        0xF0, 0xF1, 0xF2, 0xF3,
        0xF4, 0xF5, 0xF6, 0xF7,
        0xF8, 0xF9, 0xFA, 0xFB,
        0xFC, 0xFD, 0xFE, 0xFF };
/**
 * @brief The name of the adventure menu items is important starting at City of Bywater
 */
 std::vector<std::string> MenuEntries {
     "",
    "Begin New Adventure",
    "",
    "End This Adventure",
    "",
    "Install Divinity Scenario",
    "Uninstall Divinity Scenario",
    "New Scenario",
    "Tutorial",
    "",
    "City of Bywater",
    "Prelude to Pestilence",
    "Assault on Giant Mountain",
    "Destroy The Necronomicon",
    "Castle in the Clouds",
    "Grilochs Revenge",
    "White Dragon",
    "Mithril Vault",
    "Twin Sands of Time",
    "Trouble in the Sword Lands",
    "War in the Sword Lands",
    "Dagger of Silences",
    "Half Truth",
};
constexpr uint32_t TranslateUintToProperCharacter2(uint32_t param_1) noexcept {
    if (param_1 == 0xffffffff) {
        return 0xffffffff;
    } else {
        return translationTable[param_1 & 0xff];
    }
}
int
strlen_goofy(const std::string& input) {
    auto oddCounter = -1;
    char currentCharacter = 0;
    const char* ptr = input.c_str();
    do {
        if (oddCounter == 0) {
            break;
        }
        oddCounter += -1;
        currentCharacter = *ptr;
        ++ptr;
    } while(currentCharacter != 0);
    return -2 - oddCounter;
}
template<typename T>
int
strlen_goofy(T begin, T end) noexcept {
    auto oddCounter = -1;
    char currentCharacter = 0;
    do {
        if (oddCounter == 0) {
            break;
        }
        oddCounter += -1;
        currentCharacter = *begin;
        if (currentCharacter == 0) {
            break;
        }
        ++begin;
    } while (begin != end);
    return -2 - oddCounter;
}
std::string
transform(const std::string& input) noexcept {
    std::stringstream ss;
    for (auto c : input) {
        ss.put(TranslateUintToProperCharacter2(c) & 0xFF);
    }
    auto result = ss.str();
    return result;
}
using KeyStorageBlock = std::array<char, 0x14>;
KeyStorageBlock primaryScenarioBlock0 = { 0 };
KeyStorageBlock primaryScenarioBlock1 = { 0 };
KeyStorageBlock DataCD0 = { 0 };
KeyStorageBlock DataCD1 = { 0 };
uint32_t licenseDenominator = 0;
uint32_t licenseConstant = 0;

constexpr uint32_t swapBytes(uint32_t value) noexcept {
    if (value == 0 || value == 0xffff'ffff) {
        return value;
    } else {
        auto lowest = (value & 0xFF) << 24;
        auto lower = (value & 0xFF00) << 8;
        auto higher = (value & 0xFF0000) >> 8;
        auto highest = (value & 0xFF000000) >> 24;
        return lowest | lower | higher | highest;
    }
}
static_assert(swapBytes(0x1000'0000) == 0x10);
static_assert(swapBytes(0x0011'0011) == 0x11001100);

auto populateCommonConstants(const std::filesystem::path& realmzRoot, const std::string& scenarioName) {

    auto scenarioLocation = realmzRoot / "Scenarios" / scenarioName;
    auto primaryData = scenarioLocation / scenarioName;
    std::ifstream pdata(primaryData);
    if (!pdata.is_open()) {
        return false;
    }
    // load components as needed to generate the parts the needed for key generation
    pdata.read(reinterpret_cast<char*>(&licenseDenominator), 4);
    pdata.read(reinterpret_cast<char*>(&licenseConstant), 4);
    /// @todo disable this swap code if we are on a big endian system
    licenseDenominator = swapBytes(licenseDenominator);
    licenseConstant = swapBytes(licenseConstant);
    // skip the next 12 bytes
    pdata.seekg(12);
    // now pull the primary and secondary data components in
    pdata.read(primaryScenarioBlock0.data(), 0x14);
    pdata.read(primaryScenarioBlock1.data(), 0x14);
    pdata.close();
    std::ifstream datacd(scenarioLocation / "Data CS");
    if (!datacd.is_open()) {
        // try "DATA CS" instead because case sensitivity isn't a thing outside nix systems... T_T
        datacd.close();
        datacd.open(scenarioLocation / "DATA CS");
        if (!datacd.is_open()) {
            return false;
        }
    }
    // once again jump past the initial 20 bytes
    datacd.seekg(20);
    datacd.read(DataCD0.data(), 0x14);
    datacd.read(DataCD1.data(), 0x14);
    datacd.close();
    return true;
}

int32_t transformRegistrationName(int32_t serialNumber, const std::string& registrationName) {
    auto count = serialNumber;
    for (int index = 1; ;++index) {
        auto c = registrationName[index];
        auto prevC = registrationName[index -1];
        auto goof = strlen_goofy(registrationName);
        if (goof <= static_cast<unsigned int>(index)) {
            break;
        }
        if (c != 0) {
            auto i0 = count + (c * index);
            auto i1 = static_cast<int>(prevC) * static_cast<int>(c);
            count = i0 - i1;
        }
    }
    return count;
}

constexpr int32_t computeCoefficient2(int32_t serialNumber, int32_t coefficient1) noexcept {
    auto p0 = serialNumber / 0x14d;
    auto p1 = p0 + 0x1c2;
    auto p2 = coefficient1 * 0x60;
    auto p3 = coefficient1 + 999;
    auto p4 = p0 * 0x1c8;
    return ((p1 % p2) * 0x200) + (p3 % p4) + 999;
}
void generateFantasoftScenarioKeys(std::ostream& out, const std::string& registrationName, int32_t serialNumber, int32_t menuConstant, const std::filesystem::path& realmzRoot) {
    // get the name associated with the menu constant
    if (!populateCommonConstants(realmzRoot, MenuEntries[menuConstant])) {
        return;
    }
    auto transformedRegistrationName = transform(registrationName);
    auto registrationNameCoefficient = transformRegistrationName(serialNumber, transformedRegistrationName);
    auto computedRegistrationNumber = serialNumber / ((menuConstant - 5) * 0x29a);
    // these are broken up into many lines to prevent confusion
    auto p0 = computedRegistrationNumber + 0x200;
    auto p1 = registrationNameCoefficient * 0x80;
    auto p2 = p0 % p1;
    auto p3 = p2 * 0x100;
    auto p4 = (registrationNameCoefficient + 0x400);
    auto p5 = computedRegistrationNumber * 0x200;
    auto p6 = p4 % p5;
    auto p7 = p3 + p6 + 0x400;
    auto p8 = p7 * licenseConstant;
    auto p9 = p8 + -0x200;
    auto p10 = p9/ licenseDenominator;
    auto style2Key = p10 + 0x12;
    out << MenuEntries[menuConstant] << ": " << style2Key << std::endl;
}
void generateCustomScenarioKeys(std::ostream& out, const std::string& registrationName, int32_t serialNumber, const std::string& scenarioName, const std::filesystem::path& realmzRoot) {
    if (scenarioName.empty()) {
        return;
    }
    if (!populateCommonConstants(realmzRoot, scenarioName)) {
        return;
    }
    for (int i = 0; i < 0x14; ++i) {
        primaryScenarioBlock1[i] = primaryScenarioBlock1[i] - DataCD0[i];
        primaryScenarioBlock0[i] = primaryScenarioBlock0[i] - primaryScenarioBlock1[i];
    }
    for (int i = 0; i < 0x14; ++i) {
        primaryScenarioBlock0[i] = TranslateUintToProperCharacter2(primaryScenarioBlock0[i]);
        primaryScenarioBlock1[i] = TranslateUintToProperCharacter2(primaryScenarioBlock1[i]);
    }
    auto transformedRegistrationName = transform(registrationName);
    auto registrationNameCoefficient = transformRegistrationName(serialNumber, transformedRegistrationName);
    auto theKey = computeCoefficient2(serialNumber, registrationNameCoefficient);
    for (int i = 0; ; ++i) {
        auto goof = strlen_goofy(primaryScenarioBlock0.begin(), primaryScenarioBlock0.end());
        if (goof <= static_cast<unsigned int>(i)) {
            break;
        }
        theKey += static_cast<int16_t>(primaryScenarioBlock0[i]) * 0x699;
    }

    for (int i = 0; ; ++i) {
        auto goof = strlen_goofy(primaryScenarioBlock1.begin(), primaryScenarioBlock1.end());
        if (goof <= i) {
            break;
        }
        theKey -= static_cast<int16_t>(primaryScenarioBlock1[i]) * 0x1a7;
    }
    auto transformedScenarioName = transform(scenarioName);
    for (int i = 0; ; ++i) {
        auto goof = strlen_goofy(transformedScenarioName);
        if (goof <= i) {
            break;
        }
        theKey += transformedScenarioName[i] * 0x1b669;
    }
    std::cout << scenarioName << ": " << theKey << std::endl;
}
void generateKeys(std::ostream& out, const std::string& registrationName, int32_t serialNumber, int32_t menuConstant, const std::filesystem::path& realmzRoot) {
   if (menuConstant < 10)  {
       // don't do anything when the menu constant is less than equal to 10
       // the City of Bywater scenario does not have a license check in it
       return;
   } else if (menuConstant > 0x17) {
       generateCustomScenarioKeys(out, registrationName, serialNumber, "", realmzRoot);
       // we need to do a different method of key generation, what I used to call style 1
   } else {
        generateFantasoftScenarioKeys(out, registrationName, serialNumber, menuConstant, realmzRoot);
   }
}

constexpr int32_t
generateRegistrationCode(int32_t serialNumber) noexcept {
    auto p0 = serialNumber / 6;
    auto p1 = serialNumber >> 31;
    auto p2 = p0 + p1;
    auto p3 = p2 >> 2;
    auto p4 = p3 - p1;
    auto p5 = p4 + 48;
    auto p6 = p5* 14;
    auto p7 = p6 - 28;
    return p7;
}

int
main() {
    int32_t serialNumber = 0;
    std::string registrationName, realmzRoot;
    std::cout << "Enter Serial Number: ";
    std::cin >> serialNumber;
    std::cout << "Enter Registration Name: ";
    std::cin >> registrationName;
    std::cout << "Enter path to Realmz directory: ";
    // have to read twice
    std::getline(std::cin, realmzRoot);
    std::getline(std::cin, realmzRoot);
    std::filesystem::path realmzDir(realmzRoot);

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Serial Number: " << std::dec << serialNumber << std::endl;
    std::cout << "Registration Number: " << std::dec << generateRegistrationCode(serialNumber) << std::endl;
    std::cout << "Reset Serial Number Code: 410" << std::endl;
    std::cout << "Registration Name: " << registrationName << std::endl;
    for (int i = 0; i < MenuEntries.size(); ++i) {
        generateKeys(std::cout, registrationName, serialNumber, i, realmzDir);
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;


    return 0;
}
