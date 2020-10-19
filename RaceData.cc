//
// Created by jwscoggins on 9/20/20.
//
#include <filesystem>
#include <map>
#include <optional>
#include <fstream>
#include "RaceData.h"
#include "RaceDataBuffer.h"

namespace realmz {
    Hatred::Hatred(const RaceDataBuffer &buffer) : Hatred(buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6], buffer[7]) { }

    RaceData::RaceData(const RaceDataBuffer &buf) :
    _hatred(buf),
    _specialAbilities(buf),
    _drvs(buf),
    _attributes(buf),
    _unused1(buf[96]),
    _unused2(buf[97]),
    _baseMovementPoints(buf[98]),
    _magicResistance(buf[99]),
    _twoHandedAdjustment(buf[100]),
    _missileWeaponAdjust(buf[101]),
    _attacksPerRound(buf[102]),
    _maxAttacksPerRound(buf[103]),
    _canRegenerate(buf[166] >> 8),
    _portraitId(buf[167]),
    _ineligibilityBits(buf[172])
    {
        for (int i = 48, j = 0; i < 48 + 8; ++i, ++j) {
            _unused0[j] = buf[i];
        }
        for (int i = 56, j = 0; i < 96; ++i, ++j) {
            _conditions[j] = buf[i];
        }
        for (int i = 104, j = 0; i < 119; ++i, j+=2) {
            // its two bytes per entry
            _flags[j] = buf[i] & 0xFF;
            _flags[j+1] = (buf[i] >> 8) & 0xFF;
        }
        for (int i = 119,j = 0; i < 129; i+=2, ++j) {
            auto from = buf[i];
            auto to = buf[i+1];
            _ageRanges[j] = AgeRange(from, to);
        }
        // these are chars which are not buffered
        // manually unpack to be on the safe side
        // This code is gross being manually extracted but I want it working correctly rather than compact
        auto pos0 = buf[129];
        auto pos1 = buf[130];
        auto pos2 = buf[131];
        auto pos3 = buf[132];
        auto pos4 = buf[133];
        auto pos5 = buf[134];
        auto pos6 = buf[135];
        auto pos7 = buf[136]; // this spans two parts
        auto pos8 = buf[137];
        auto pos9 = buf[138];
        auto pos10 = buf[139];
        auto pos11 = buf[140];
        auto pos12 = buf[141];
        auto pos13 = buf[142];
        auto pos14 = buf[143]; // does not span
        auto pos15 = buf[144];
        auto pos16 = buf[145];
        auto pos17 = buf[146];
        auto pos18 = buf[147];
        auto pos19 = buf[148];
        auto pos20 = buf[149];
        auto pos21 = buf[150];
        auto pos22 = buf[151]; // does span
        auto pos23 = buf[152];
        auto pos24 = buf[153];
        auto pos25 = buf[154];
        auto pos26 = buf[155];
        auto pos27 = buf[156];
        auto pos28 = buf[157];
        auto pos29 = buf[158]; // does not span
        auto pos30 = buf[159];
        auto pos31 = buf[160];
        auto pos32 = buf[161];
        auto pos33 = buf[162];
        auto pos34 = buf[163];
        auto pos35 = buf[164];
        auto pos36 = buf[165];
        auto pos37 = buf[166]; // spans
        _ageModifiers[0] = AgeModifiers(pos0, pos0>>8,
                                        pos1, pos1>>8,
                                        pos2, pos2>>8,
                                        pos3, pos3>>8,
                                        pos4, pos4>>8,
                                        pos5, pos5>>8,
                                        pos6, pos6>>8,
                                        pos7);
        _ageModifiers[1] = AgeModifiers(pos7>>8,
                                        pos8, pos8 >> 8,
                                        pos9, pos9>>8,
                                        pos10, pos10>>8,
                                        pos11, pos11>>8,
                                        pos12, pos12>>8,
                                        pos13, pos13>>8,
                                        pos14, pos14>>8 );
        _ageModifiers[2] = AgeModifiers(pos15, pos15>>8,
                                        pos16, pos16>>8,
                                        pos17, pos17>>8,
                                        pos18, pos18 >>8,
                                        pos19, pos19>>8,
                                        pos20, pos20>>8,
                                        pos21, pos21>>8,
                                        pos22);
        _ageModifiers[3] = AgeModifiers(pos22 >>8,
                                        pos23, pos23>>8,
                                        pos24, pos24>>8,
                                        pos25, pos25>>8,
                                        pos26, pos26>>8,
                                        pos27, pos27>>8,
                                        pos28, pos28>>8,
                                        pos29, pos29>>8);
        _ageModifiers[4] = AgeModifiers(pos30, pos30>>8,
                                        pos31, pos31>>8,
                                        pos32, pos32>>8,
                                        pos33, pos33>>8,
                                        pos34, pos34>>8,
                                        pos35, pos35>>8,
                                        pos36, pos36>>8,
                                        pos37 );
        // allowedBits, need to figure out if I got the bit ordering correct or not :)
        auto lowest = buf[168];
        auto lower = buf[169];
        int32_t lowerHalf = (static_cast<int32_t>(lowest) & 0xFFFF) | ((static_cast<int32_t>(lower) << 16) & 0xFFFF0000);
        auto higher = buf[170];
        auto highest = buf[171];
        int32_t upperHalf = (static_cast<int32_t>(higher) & 0xFFFF) | ((static_cast<int32_t>(highest) << 16) & 0xFFFF0000);
        _allowedBits = ((static_cast<int64_t>(upperHalf) << 32) & 0xFFFF'FFFF'0000'0000) | ((static_cast<int64_t>(lowerHalf)) & 0x0000'0000'FFFF'FFFF);

    }
    namespace {
        bool loadedRaceData = false;
        std::filesystem::path raceDataLocation;
        std::map<RaceKind, RaceData> registeredRaceData;
        void
        loadRaceData() {
            if (loadedRaceData) {
                return;
            }
            auto readOne = [](std::istream& input) -> std::optional<RaceData> {
                RaceDataBuffer buf;
                input.read((char *) buf.data(), RaceDataBufferNumBytes);
                if (input.gcount() != RaceDataBufferNumBytes) {
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
                return RaceData(buf);
            };
            std::ifstream raceDataFile(raceDataLocation);
            if (!raceDataFile.is_open()) {
                throw "Couldn't open caste data file";
            }
            for (int curr = static_cast<int>(RaceKind::Human);  curr != static_cast<int>(RaceKind::Done); ++curr) {
                auto theCaste = static_cast<RaceKind>(curr);
                if (auto result = readOne(raceDataFile); result) {
                    registeredRaceData.emplace(theCaste, *result);
                } else {
                    throw "Couldn't load all entries";
                }
            }
            raceDataFile.close();
            loadedRaceData = true;
        }
    }
    void
    setRaceDataLocation(const std::filesystem::path& path) noexcept {
        raceDataLocation = path;
        loadedRaceData = false;
    }
    bool
    raceDataLocationSet() noexcept {
        return loadedRaceData;
    }
    const RaceData&
    loadRaceData(RaceKind kind) {
        loadRaceData();
        if (registeredRaceData.empty()) {
            throw "Race data not loaded";
        } else {
            if (auto pos = registeredRaceData.find(kind); pos != registeredRaceData.end()) {
                return pos->second;
            } else {
                throw "Unknown race kind!";
            }
        }
    }
}

std::ostream &
operator<<(std::ostream &os, realmz::RaceKind r) noexcept {
    switch (r) {
#define Y(k, s) case realmz::RaceKind:: k : os << s
#define X(k) Y(k, #k)
        X(Human);
        Y(ShadowElf, "Shadow Elf");
        X(Elf);
        X(Orc);
        X(Furfoot);
        X(Gnome);
        X(Dwarf);
        Y(HalfElf, "Half Elf");
        Y(HalfOrc, "Half Orc");
        X(Goblin);
        X(Hobgoblin);
        X(Kobold);
        X(Vampire);
        Y(LizardMan, "Lizard Man");
        X(Brownie);
        X(Pixie);
        X(Leprechaun);
        X(Demon);
        X(Cathoon);
#undef X
#undef Y
        default:
            os << "UNKNOWN!";
    }
    return os;
}
