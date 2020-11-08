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

    SneakAttack,
    CauseMajorWound,
    DetectSecret,
    AcrobaticAct,
    DetectTrap,
    DisableTrap,
    ForceLock,
    PickLock,
    TurnUndead,
    MagicAura,
    ShieldedFromNormalAttacks,
    ShieldedFromProjectiles,
    Regenerate,
    ProtectionFromHeatAttacks,
    ProtectionFromColdAttacks,
    ProtectionFromElectricalAttacks,
    ProtectionFromChemicalAttacks,
    ProtectionFromMentalAttacks,
    ProtectionFrom1stLevelSpells,
    ProtectionFrom2ndLevelSpells,
    ProtectionFrom3rdLevelSpells,
    ProtectionFrom4thLevelSpells,
    ProtectionFrom5thLevelSpells,
    Strong,
    ProtectionFromFoe,
    Speed,
    Invisible,
    ReflectingSpells,
    ReflectingAttacks,
    AttackBonusCondition,
    AbsorbEnergy,
    AbsorbSpellEnergyFromAttacks,
    DefensiveBonus,
    VsMagicCreatures,
    VsUndeadCreatures,
    VsDemonicCreatures,
    VsReptilianCreatures,
    VsVeryEvilCreatures,
    VsIntelligentCreatures,
    VsGiantSizedCreatures,
    VsNonHumanoidCreatures,
    Count,
};

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
            case CharacterFieldIndex::SpellPointsCurrent: return mkStr(_cc->getSpellPointsCurrent());
            case CharacterFieldIndex::SpellPointsTotal: return mkStr(_cc->getSpellPointsTotal());
            case CharacterFieldIndex::StaminaCurrent: return mkStr(_cc->getStaminaCurrent());
            case CharacterFieldIndex::StaminaTotal: return mkStr(_cc->getStaminaTotal());
            case CharacterFieldIndex::ArmorRating: return mkStr(_cc->getArmorRating());
            case CharacterFieldIndex::MagicResistance: return mkStr(_cc->getMagicResistance());
            case CharacterFieldIndex::CharmDRV: return mkStr(_cc->getDamageReductionVsCharm());
            case CharacterFieldIndex::HeatDRV: return mkStr(_cc->getDamageReductionVsHeat());
            case CharacterFieldIndex::ColdDRV: return mkStr(_cc->getDamageReductionVsCold());
            case CharacterFieldIndex::ElectricDRV: return mkStr(_cc->getDamageReductionVsElectric());
            case CharacterFieldIndex::ChemicalDRV: return mkStr(_cc->getDamageReductionVsChemical());
            case CharacterFieldIndex::MentalDRV: return mkStr(_cc->getDamageReductionVsMental());
            case CharacterFieldIndex::MagicDRV: return mkStr(_cc->getDamageReductionVsMagic());
            case CharacterFieldIndex::SpecialDRV: return mkStr(_cc->getDamageReductionVsSpecial());
            case CharacterFieldIndex::Gold: return mkStr(_cc->getGold());
            case CharacterFieldIndex::Gems: return mkStr(_cc->getGems());
            case CharacterFieldIndex::Jewelry: return mkStr(_cc->getJewelry());
            case CharacterFieldIndex::SpellSelectionPoints: return mkStr(_cc->getSpellSelectionPoints());
            case CharacterFieldIndex::SneakAttack: return mkStr(_cc->getSpecialInfo().getSneakAttack());
            case CharacterFieldIndex::CauseMajorWound: return mkStr(_cc->getSpecialInfo().getCauseMajorWound());
            case CharacterFieldIndex::DetectSecret: return mkStr(_cc->getSpecialInfo().getDetectSecret());
            case CharacterFieldIndex::AcrobaticAct: return mkStr(_cc->getSpecialInfo().getAcrobaticAct());
            case CharacterFieldIndex::DetectTrap: return mkStr(_cc->getSpecialInfo().getDetectTrap());
            case CharacterFieldIndex::DisableTrap: return mkStr(_cc->getSpecialInfo().getDisableTrap());
            case CharacterFieldIndex::ForceLock: return mkStr(_cc->getSpecialInfo().getForceLock());
            case CharacterFieldIndex::PickLock: return mkStr(_cc->getSpecialInfo().getPickLock());
            case CharacterFieldIndex::TurnUndead: return mkStr(_cc->getSpecialInfo().getTurnUndead());
            case CharacterFieldIndex::MagicAura: return mkStr(_cc->getConditions().getConditionMagicAura());
            case CharacterFieldIndex::ShieldedFromNormalAttacks: return mkStr(_cc->getConditions().getConditionShieldedFromNormalAttacks());
            case CharacterFieldIndex::ShieldedFromProjectiles: return mkStr(_cc->getConditions().getConditionShieldedFromProjectiles());
            case CharacterFieldIndex::Regenerate: return mkStr(_cc->getConditions().getRegenerating());
            case CharacterFieldIndex::ProtectionFromHeatAttacks: return mkStr(_cc->getConditions().getProtectionFromHeatAttacks());
            case CharacterFieldIndex::ProtectionFromColdAttacks: return mkStr(_cc->getConditions().getProtectionFromColdAttacks());
            case CharacterFieldIndex::ProtectionFromElectricalAttacks: return mkStr(_cc->getConditions().getProtectionFromElectricalAttacks());
            case CharacterFieldIndex::ProtectionFromChemicalAttacks: return mkStr(_cc->getConditions().getProtectionFromChemicalAttacks());
            case CharacterFieldIndex::ProtectionFromMentalAttacks: return mkStr(_cc->getConditions().getProtectionFromMentalAttacks());
            case CharacterFieldIndex::ProtectionFrom1stLevelSpells: return mkStr(_cc->getConditions().getProtectionFrom1stLevelSpells());
            case CharacterFieldIndex::ProtectionFrom2ndLevelSpells: return mkStr(_cc->getConditions().getProtectionFrom2ndLevelSpells());
            case CharacterFieldIndex::ProtectionFrom3rdLevelSpells: return mkStr(_cc->getConditions().getProtectionFrom3rdLevelSpells());
            case CharacterFieldIndex::ProtectionFrom4thLevelSpells: return mkStr(_cc->getConditions().getProtectionFrom4thLevelSpells());
            case CharacterFieldIndex::ProtectionFrom5thLevelSpells: return mkStr(_cc->getConditions().getProtectionFrom5thLevelSpells());
            case CharacterFieldIndex::Strong: return mkStr(_cc->getConditions().getStrong());
            case CharacterFieldIndex::ProtectionFromFoe: return mkStr(_cc->getConditions().getProtectionFromFoe());
            case CharacterFieldIndex::Speed: return mkStr(_cc->getConditions().getSpeedy());
            case CharacterFieldIndex::Invisible: return mkStr(_cc->getConditions().getInvisible());
            case CharacterFieldIndex::ReflectingSpells: return mkStr(_cc->getConditions().getReflectingSpells());
            case CharacterFieldIndex::ReflectingAttacks: return mkStr(_cc->getConditions().getReflectingAttacks());
            case CharacterFieldIndex::AttackBonusCondition: return mkStr(_cc->getConditions().getBonusDamage());
            case CharacterFieldIndex::AbsorbEnergy: return mkStr(_cc->getConditions().getAbsorbEnergy());
            case CharacterFieldIndex::AbsorbSpellEnergyFromAttacks: return mkStr(_cc->getConditions().getAbsorbSpellEnergyFromAttacks());
            case CharacterFieldIndex::DefensiveBonus: return mkStr(_cc->getConditions().getDefensiveBonus());
            case CharacterFieldIndex::VsDemonicCreatures: return mkStr(_cc->getVsDemonicCreatures());
            case CharacterFieldIndex::VsMagicCreatures: return mkStr(_cc->getVsMagicUsingCreatures());
            case CharacterFieldIndex::VsUndeadCreatures: return mkStr(_cc->getVsUndeadCreatures());
            case CharacterFieldIndex::VsReptilianCreatures: return mkStr(_cc->getVsReptileCreatures());
            case CharacterFieldIndex::VsVeryEvilCreatures: return mkStr(_cc->getVsVeryEvilCreatures());
            case CharacterFieldIndex::VsIntelligentCreatures: return mkStr(_cc->getVsIntelligentCreatures());
            case CharacterFieldIndex::VsGiantSizedCreatures: return mkStr(_cc->getVsGiantSizedCreatures());
            case CharacterFieldIndex::VsNonHumanoidCreatures: return mkStr(_cc->getVsNonHumanoidCreature());
            default:
                break;
        }
    }
    return QVariant();
}

QVariant
PrimaryCharacterModel::headerData(int section, Qt::Orientation orientation, int role) const {
    static const std::array<QString, static_cast<size_t>(CharacterFieldIndex::Count)> RowHeaders {
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

            tr("Gold"), tr("Gems"), tr("Jewelry"),

            tr("Sneak Attack"), tr("Cause Major Wound"), tr("Detect Secret"),
            tr("Acrobatic Act"), tr("Detect Trap"), tr("Disable Trap"),
            tr("Force Lock"), tr("Pick Lock"), tr("Turn Undead"),
            tr("Magic Aura"), tr("Shielded From Normal Attacks"), tr("Shielded From Projectiles"),
            tr("Regenerate"),
            tr("Protection From Heat Attacks"),
            tr("Protection From Cold Attacks"),
            tr("Protection From Electrical Attacks"),
            tr("Protection From Chemical Attacks"),
            tr("Protection From Mental Attacks"),
            tr("Protection From 1st Level Spells"),
            tr("Protection From 2nd Level Spells"),
            tr("Protection From 3rd Level Spells"),
            tr("Protection From 4th Level Spells"),
            tr("Protection From 5th Level Spells"),
            tr("Strong"),
            tr("Protection From Foe"),
            tr("Speed"),
            tr("Invisible"),
            tr("Reflecting Spells"),
            tr("Reflecting Attacks"),
            tr("Attack Bonus (Condition)"),
            tr("Absorb Energy"),
            tr("Absorb Spell Energy From Attacks"),
            tr("Defensive Bonus"),
            tr("Vs Magic Using Creatures"),
            tr("Vs Undead Creatures"),
            tr("Vs Demonic Creatures"),
            tr("Vs Reptilian Creatures"),
            tr("Vs Very Evil Creatures"),
            tr("Vs Intelligent Creatures"),
            tr("Vs Giant Sized Creatures"),
            tr("Vs Non-Humanoid Creatures")

    };
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Orientation::Vertical) {
            // row
            return RowHeaders[section];
        }
    }
    return QVariant();
}
