//
// Created by jwscoggins on 11/6/20.
//

#include "PrimaryCharacterModel.h"
#include <sstream>

enum class CharacterFieldIndex {
    Name = 0,
    Skill,
    Age,
    SpellSelectionPoints,
    Gender,
    Caste,
    Race,
    VictoryPoints,
    Brawn,
    Knowledge,
    Judgment,
    Agility,
    Vitality,
    Luck,
    AttackBonus,
    DefenseBonus,
    MissileAdjust,
    DodgeMissile,
    BareHandDamage,
    MovementBonus,
    HandToHand,
    DamagePlus,
    ChanceToHit,
    SpellPointsCurrent,
    SpellPointsTotal,
    StaminaCurrent,
    StaminaTotal,
    ArmorRating,
    MagicResistance,
    CharmDRV,
    HeatDRV,
    ColdDRV,
    ElectricDRV,
    ChemicalDRV,
    MentalDRV,
    MagicDRV,
    SpecialDRV,
    Gold,
    Gems,
    Jewelry,
    Count,
};
static_assert(static_cast<int>(CharacterFieldIndex::Count) == 40);

int
PrimaryCharacterModel::rowCount(const QModelIndex& idx) const {
    return static_cast<int>(CharacterFieldIndex::Count);
}

QVariant
PrimaryCharacterModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        if (!_cc)  {
            return QVariant();
        }
        auto mkStr = [](auto value) noexcept { return QString::number(static_cast<int>(value)); };
        switch (static_cast<CharacterFieldIndex>(index.row())) {
            case CharacterFieldIndex::Name: return QString(_cc->getName().c_str());
            case CharacterFieldIndex::Age: return mkStr(_cc->getAgeInYears());
            case CharacterFieldIndex::Skill: return mkStr(_cc->getSkillLevel());
            case CharacterFieldIndex::Gender:
                switch (_cc->getGender()) {
                    case realmz::Gender::Female:
                        return tr("Female");
                    case realmz::Gender::Male:
                        return tr("Male");
                    default:
                        return tr("Undefined");
                }
                // for formatting purposes
                break;
            case CharacterFieldIndex::Caste:
                return [this]() {
                    std::stringstream ss;
                    ss << _cc->getCaste();
                    auto str = ss.str();
                    return QString(str.c_str());
                }();
            case CharacterFieldIndex::Race:
                return [this]() {
                    std::stringstream ss;
                    ss << _cc->getRace();
                    auto str = ss.str();
                    return QString(str.c_str());
                }();
            case CharacterFieldIndex::VictoryPoints: return mkStr(_cc->getVictoryPoints());
            case CharacterFieldIndex::Brawn: return mkStr(_cc->getBrawn());
            case CharacterFieldIndex::Knowledge: return mkStr(_cc->getKnowledge());
            case CharacterFieldIndex::Judgment: return mkStr(_cc->getJudgement());
            case CharacterFieldIndex::Agility: return mkStr(_cc->getAgility());
            case CharacterFieldIndex::Vitality: return mkStr(_cc->getVitality());
            case CharacterFieldIndex::Luck: return mkStr(_cc->getLuck());
            case CharacterFieldIndex::MissileAdjust: return mkStr(_cc->getMissileAdjust());
            case CharacterFieldIndex::DodgeMissile: return mkStr(_cc->getDodgeMissile());
            case CharacterFieldIndex::BareHandDamage: return mkStr(_cc->getBareHandDamage());
            case CharacterFieldIndex::MovementBonus: return mkStr(_cc->getMovementBonus());
            case CharacterFieldIndex::HandToHand: return mkStr(_cc->getHandToHandMax());
            case CharacterFieldIndex::DamagePlus: return mkStr(_cc->getDamagePlus());
            case CharacterFieldIndex::ChanceToHit: return mkStr(_cc->getChanceToHit());
            default:
                break;
        }
    }
    return QVariant();
}

QVariant
PrimaryCharacterModel::headerData(int section, Qt::Orientation orientation, int role) const {
    static const std::array<QString, 40> RowHeaders {
            tr("Name"), tr("Skill"), tr("Age"),
            tr("Spell Selection Points"), tr("Gender"), tr("Caste"),
            tr("Race"), tr("Victory Points"),
            tr("Brawn"), tr("Knowledge"), tr("Judgment"),
            tr("Agility"), tr("Vitality"), tr("Luck"),
            tr("Attack Bonus"), tr("Defense Bonus"), tr("Missile Adjust"),
            tr("Dodge Missile"), tr("Bare Hand Damage"), tr("Movement Bonus"),
            tr("Hand to Hand"), tr("Damage +"), tr("Chance To Hit"),
            tr("Spell Points Current"), tr("Spell Points Total"), tr("Stamina Current"),
            tr("Stamina Total"), tr("Armor Rating"), tr("Magic Resistance"),

            tr("DRV Charm"), tr("DRV Heat"), tr("DRV Cold"),
            tr("DRV Electric"), tr("DRV Chemical"), tr("DRV Mental"),
            tr("DRV Magic"), tr("DRV Special"),

            tr("Gold"),
            tr("Gems"),
            tr("Jewelry"),
    };
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Orientation::Vertical) {
            // row
            return RowHeaders[section];
        }
    }
    return QVariant();
}
