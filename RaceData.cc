//
// Created by jwscoggins on 9/20/20.
//
#include <filesystem>
#include <map>
#include <optional>
#include <fstream>
#include "RaceData.h"
#include "RaceDataBuffer.h"
#include "BinaryManipulation.h"

namespace realmz {
    Hatred::Hatred(const RaceDataBuffer &buffer) : Hatred(buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6], buffer[7]) { }
    RaceData::RaceData(const RaceDataBuffer &buf) :
    _hatred(buf),
    _specialAbilities(buf),
    _drvs(buf),
    _attributes(buf),
    _unused0({
        buf[48], buf[49], buf[50], buf[51],
        buf[52], buf[53], buf[54], buf[55],
    }),
    _conditions({
        buf[56], buf[57], buf[58], buf[59], buf[60],
        buf[61], buf[62], buf[63], buf[64], buf[65],
        buf[66], buf[67], buf[68], buf[69], buf[70],
        buf[71], buf[72], buf[73], buf[74], buf[75],
        buf[76], buf[77], buf[78], buf[79], buf[80],
        buf[81], buf[82], buf[83], buf[84], buf[85],
        buf[86], buf[87], buf[88], buf[89], buf[90],
        buf[91], buf[92], buf[93], buf[94], buf[95],
    }),
    _unused1(buf[96]),
    _unused2(buf[97]),
    _baseMovementPoints(buf[98]),
    _magicResistance(buf[99]),
    _twoHandedAdjustment(buf[100]),
    _missileWeaponAdjust(buf[101]),
    _attacksPerRound(buf[102]),
    _maxAttacksPerRound(buf[103]),
    _flags({
#define X(ind) lowerHalf(ind), upperHalf(ind)
                   X(104), X(105), X(106),
                   X(107), X(108), X(109),
                   X(110), X(111), X(112),
                   X(113), X(114), X(115),
                   X(116), X(117), X(118),
#undef X
    }),
    _ageRanges({
#define X(ind) AgeRange(buf[ind], buf[ind+1])
        X(119),
        X(121),
        X(123),
        X(125),
        X(127),
#undef X
    }),
    _ageModifiers({
                          // these are chars which are not buffered
                          // manually unpack to be on the safe side
                          // This code is gross being manually extracted but I want it working correctly rather than compact
                          AgeModifiers(buf[129]>>8, buf[129],
                                       buf[130]>>8, buf[130],
                                       buf[131]>>8, buf[131],
                                       buf[132]>>8, buf[132],
                                       buf[133]>>8, buf[133],
                                       buf[134]>>8, buf[134],
                                       buf[135]>>8, buf[135],
                                       buf[136]>>8),
                          AgeModifiers(buf[136],
                                       buf[137]>>8, buf[137],
                                       buf[138]>>8, buf[138],
                                       buf[139]>>8, buf[139],
                                       buf[140]>>8, buf[140],
                                       buf[141]>>8, buf[141],
                                       buf[142]>>8, buf[142],
                                       buf[143]>>8, buf[143]),
                          AgeModifiers(buf[144]>>8, buf[144],
                                       buf[145]>>8, buf[145],
                                       buf[146]>>8, buf[146],
                                       buf[147]>>8, buf[147],
                                       buf[148]>>8, buf[148],
                                       buf[149]>>8, buf[149],
                                       buf[150]>>8, buf[150],
                                       buf[151]>>8),
                          AgeModifiers(buf[151],
                                       buf[152]>>8, buf[152],
                                       buf[153]>>8, buf[153],
                                       buf[154]>>8, buf[154],
                                       buf[155]>>8, buf[155],
                                       buf[156]>>8, buf[156],
                                       buf[157]>>8, buf[157],
                                       buf[158]>>8, buf[158]),
                          AgeModifiers(buf[159]>>8, buf[159],
                                       buf[160]>>8, buf[160],
                                       buf[161]>>8, buf[161],
                                       buf[162]>>8, buf[162],
                                       buf[163]>>8, buf[163],
                                       buf[164]>>8, buf[164],
                                       buf[165]>>8, buf[165],
                                       buf[166]>>8),
                  }),
    _canRegenerate(static_cast<uint8_t>(buf[166])),
    _portraitId(buf[167]),
            // allowedBits, need to figure out if I got the bit ordering correct or not :)
    _allowedBits(make(buf[168], buf[169], buf[170], buf[171], ConstructInt64{})),
    _ineligibilityBits({
        buf[172],
        buf[173], buf[174], buf[175],
        buf[176], buf[177], buf[178],
        buf[179], buf[180], buf[181],
        buf[182], buf[183], buf[184],
        buf[185], buf[186], buf[187],
        buf[188], buf[189], buf[190],
        buf[191], buf[192], buf[193],
        buf[194], buf[195], buf[196],
        buf[197], buf[198], buf[199],
        buf[200], buf[201], buf[202],
        buf[203],
    })
    {

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
    int16_t
    RaceData::getIneligibilityBits(size_t index) const {
        if (index >= 32) {
            throw "Out of range";
        } else {
            return _ineligibilityBits[index];
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
#define Y(k, s) case realmz::RaceKind:: k : os << s; break
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
