//
// Created by jwscoggins on 10/16/20.
//

#include "Item.h"
#include "Utilities.h"

namespace realmz {
    Item::Item(const RawData &buf)
            : _brawn(buf[0]),
              _index(buf[1]),
              _iconIndex(buf[2]),
              _type(buf[3]),
              _unknown0(buf[4]),
              _numberOfHands(buf[5]),
              _luck(buf[6]),
              _movement(buf[7]),
              _armorRating(buf[8]),
              _magicResistance(buf[9]),
              _magicPlus(buf[10]),
              _spellPoints(buf[11]),
              _unknown1(buf[12]),
              _weight(buf[13]),
              _isUniqueItem(buf[14]),
              _flags(buf[15]),
              _isWearable(buf[16]),
              _unknown2(buf[17]),
              // swap the order of the words to make it little endian, this sort of nonsense is why I want to migrate
              // the binary formats to apache avro so that endianness is just handled by the act of packing and unpacking
              _allowedBits(make(buf[21], buf[20], buf[19], buf[18], realmz::ConstructInt64{})),
              _raceIneligibility(buf[22]),
              _casteIneligibility(buf[23]),
              _specificToAGivenRace(buf[24]),
              _specificToAGivenCaste(buf[25]),
              _raceUsability(buf[26]),
              _casteUsability(buf[27]),
              _unknown3({ buf[28],
                          buf[29],
                          buf[30],
                          buf[31],
                          buf[32],
                          buf[33],
                          buf[34],
                        }),
              _baseDamage(buf[35]),
              _unknown4(buf[36]),
              _heatDamage(buf[37]),
              _coldDamage(buf[38]),
              _electricDamage(buf[39]),
              _undeadDamage(buf[40]),
              _demonicDamage(buf[41]),
              _evilDamage(buf[42]),
              _abilities0(buf[43]),
              _spellCastingAbilities(buf[44]),
              _hasEnhancementModifier(buf[45]),
              _enhancementModifierIndex(buf[46]),
              _enhancementModifier(buf[47]),
              _itemCount(buf[48]),
              _unknown5(buf[49])
    {

    }
}