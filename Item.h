//
// Created by jwscoggins on 10/16/20.
//

#ifndef REALMZ_TOOLS_ITEM_H
#define REALMZ_TOOLS_ITEM_H
#include <cstdint>
#include <array>
namespace realmz {
    class Item {
    public:
        using RawData = std::array<int16_t, 100/2>;
    public:
        explicit Item(const RawData& buf);
        [[nodiscard]] constexpr int16_t getBrawn() const noexcept { return _brawn; }
        [[nodiscard]] constexpr int16_t getIndex() const noexcept { return _index; }
        [[nodiscard]] constexpr int16_t getIconIndex() const noexcept { return _iconIndex; }
        [[nodiscard]] constexpr int16_t getType() const noexcept { return _type; }
        [[nodiscard]] constexpr int16_t getUnknown0() const noexcept { return _unknown0; }
        [[nodiscard]] constexpr int16_t getNumberOfHands() const noexcept { return _numberOfHands; }
        [[nodiscard]] constexpr int16_t getLuck() const noexcept { return _luck; }
        [[nodiscard]] constexpr int16_t getMovement() const noexcept { return _movement; }
        [[nodiscard]] constexpr int16_t getArmorRating() const noexcept { return _armorRating; }
        [[nodiscard]] constexpr int16_t getMagicResistance() const noexcept { return _magicResistance; }
        [[nodiscard]] constexpr int16_t getMagicPlus() const noexcept { return _magicPlus; }
        [[nodiscard]] constexpr int16_t getSpellPoints() const noexcept { return _spellPoints; }
        [[nodiscard]] constexpr int16_t getUnknown1() const noexcept { return _unknown1; }
        [[nodiscard]] constexpr int16_t getWeight() const noexcept { return _weight; }
        [[nodiscard]] constexpr int16_t getIsUniqueItem() const noexcept { return _isUniqueItem; }
        [[nodiscard]] constexpr uint16_t getFlags() const noexcept { return _flags; }
        [[nodiscard]] constexpr int16_t getIsWearable() const noexcept { return _isWearable; }
        [[nodiscard]] constexpr int16_t getUnknown2() const noexcept { return _unknown2; }
        [[nodiscard]] constexpr int64_t getAllowedBits() const noexcept { return _allowedBits; }
        [[nodiscard]] constexpr int16_t getRaceIneligibility() const noexcept { return _raceIneligibility; }
        [[nodiscard]] constexpr int16_t getCasteIneligibility() const noexcept { return _casteIneligibility; }
        [[nodiscard]] constexpr int16_t getSpecificToAGivenRace() const noexcept { return _specificToAGivenRace; }
        [[nodiscard]] constexpr int16_t getSpecificToAGivenCaste() const noexcept { return _specificToAGivenCaste; }
        [[nodiscard]] constexpr int16_t getRaceUsability() const noexcept { return _raceUsability; }
        [[nodiscard]] constexpr int16_t getCasteUsability() const noexcept { return _casteUsability; }
        [[nodiscard]] constexpr const std::array<int16_t, 7> &getUnknown3() const noexcept { return _unknown3; }
        [[nodiscard]] constexpr int16_t getBaseDamage() const noexcept { return _baseDamage; }
        [[nodiscard]] constexpr int16_t getUnknown4() const noexcept { return _unknown4; }
        [[nodiscard]] constexpr int16_t getHeatDamage() const noexcept { return _heatDamage; }
        [[nodiscard]] constexpr int16_t getColdDamage() const noexcept { return _coldDamage; }
        [[nodiscard]] constexpr int16_t getElectricDamage() const noexcept { return _electricDamage; }
        [[nodiscard]] constexpr int16_t getUndeadDamage() const noexcept { return _undeadDamage; }
        [[nodiscard]] constexpr int16_t getDemonicDamage() const noexcept { return _demonicDamage; }
        [[nodiscard]] constexpr int16_t getEvilDamage() const noexcept { return _evilDamage; }
        [[nodiscard]] constexpr int16_t getAbilities0() const noexcept { return _abilities0; }
        [[nodiscard]] constexpr int16_t getSpellCastingAbilities() const noexcept { return _spellCastingAbilities; }
        [[nodiscard]] constexpr int16_t getHasEnhancementModifier() const noexcept { return _hasEnhancementModifier; }
        [[nodiscard]] constexpr int16_t getEnhancementModifierIndex() const noexcept { return _enhancementModifierIndex; }
        [[nodiscard]] constexpr int16_t getEnhancementModifier() const noexcept { return _enhancementModifier; }
        [[nodiscard]] constexpr int16_t getItemCount() const noexcept { return _itemCount; }
        [[nodiscard]] constexpr int16_t getUnknown5() const noexcept { return _unknown5; }
    private:
        int16_t _brawn = 0;
        int16_t _index = 0;
        int16_t _iconIndex = 0;
        int16_t _type = 0;
        int16_t _unknown0 = 0;
        int16_t _numberOfHands = 0;
        int16_t _luck = 0;
        int16_t _movement = 0;
        int16_t _armorRating = 0;
        int16_t _magicResistance = 0;
        int16_t _magicPlus = 0;
        int16_t _spellPoints = 0;
        int16_t _unknown1 = 0;
        int16_t _weight = 0;
        int16_t _isUniqueItem = 0;
        uint16_t _flags = 0;
        int16_t _isWearable = 0;
        int16_t _unknown2 = 0;
        uint64_t _allowedBits = 0;
        int16_t _raceIneligibility = 0;
        int16_t _casteIneligibility = 0;
        int16_t _specificToAGivenRace = 0;
        int16_t _specificToAGivenCaste = 0;
        int16_t _raceUsability = 0;
        int16_t _casteUsability = 0;
        std::array<int16_t, 7> _unknown3 = { 0 };
        int16_t _baseDamage = 0;
        int16_t _unknown4 = 0;
        int16_t _heatDamage = 0;
        int16_t _coldDamage = 0;
        int16_t _electricDamage = 0;
        int16_t _undeadDamage = 0;
        int16_t _demonicDamage = 0;
        int16_t _evilDamage = 0;
        int16_t _abilities0 = 0;
        int16_t _spellCastingAbilities = 0;
        int16_t _hasEnhancementModifier = 0;
        int16_t _enhancementModifierIndex = 0;
        int16_t _enhancementModifier = 0;
        int16_t _itemCount = 0;
        int16_t _unknown5 = 0;
    };
}

#endif //REALMZ_TOOLS_ITEM_H
