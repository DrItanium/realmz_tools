#include <QLineEdit>
#include "casteinfopanel.h"
#include "ui_casteinfopanel.h"
#include "../Caste.h"
#include "../AgeGroup.h"

CasteInfoPanel::CasteInfoPanel(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::CasteInfoPanel)
{
    ui->setupUi(this);
    // on initialization we have to force the fighter data
    installCaste(realmz::loadCaste(ck));
}

CasteInfoPanel::~CasteInfoPanel()
{
    delete ui;
}

void
CasteInfoPanel::installCaste(const realmz::Caste &targetCaste)
{
    emit updateCoreStats(targetCaste.getAttributes());
    auto setInitialAndLevelUp = [](QLineEdit* initial, QLineEdit* lvlUp, const realmz::Ability& ability) {
        initial->setText(QString::number(ability.getInitial()));
        lvlUp->setText(QString::number(ability.getLevelUp()));
    };
    setInitialAndLevelUp(ui->sneakInitial, ui->sneakLvlUp, targetCaste.getInitialAbilities().getSneakAttack());
    setInitialAndLevelUp(ui->majorWoundInitial, ui->majorWoundLvlUp, targetCaste.getInitialAbilities().getMajorWound());
    setInitialAndLevelUp(ui->detectSecretInitial, ui->detectSecretLvlUp, targetCaste.getInitialAbilities().getDetectSecret());
    setInitialAndLevelUp(ui->acrobaticActInitial, ui->acrobaticActLvlUp, targetCaste.getInitialAbilities().getAcrobaticAct());
    setInitialAndLevelUp(ui->detectTrapInitial, ui->detectTrapLvlUp, targetCaste.getInitialAbilities().getDetectTrap());
    setInitialAndLevelUp(ui->disableTrapInitial, ui->disableTrapLvlUp, targetCaste.getInitialAbilities().getDisableTrap());
    setInitialAndLevelUp(ui->forceLockInitial, ui->forceLockLvlUp, targetCaste.getInitialAbilities().getForceLock());
    setInitialAndLevelUp(ui->pickLockInitial, ui->pickLockLvlUp, targetCaste.getInitialAbilities().getPickLock());
    setInitialAndLevelUp(ui->turnUndead, ui->turnUndeadLvlUp, targetCaste.getInitialAbilities().getTurnUndead());
    setInitialAndLevelUp(ui->staminaInitial, ui->staminaLevelUp, targetCaste.getStamina());
    setInitialAndLevelUp(ui->meleeAttackInitial, ui->meleeAttackLevelUp, targetCaste.getMeleeAttack());
    setInitialAndLevelUp(ui->missileAttackInitial, ui->missileAttackLevelUp, targetCaste.getMissileAttack());
    setInitialAndLevelUp(ui->dodgeMissileInitial, ui->dodgeMissileLevelUp, targetCaste.getDodgeMissile());
    setInitialAndLevelUp(ui->handToHandInitial, ui->handToHandLevelUp, targetCaste.getHandToHand());
    auto setFieldWithInteger = [](QLineEdit* le, int value) { le->setText(QString::number(value)); };
    const auto& drvs = targetCaste.getDRVs();
    setFieldWithInteger(ui->charmDrv, drvs.getCharm());
    setFieldWithInteger(ui->coldDrv, drvs.getCold());
    setFieldWithInteger(ui->heatDrv, drvs.getHeat());
    setFieldWithInteger(ui->electricDrv, drvs.getElectric());
    setFieldWithInteger(ui->chemicalDrv, drvs.getChemical());
    setFieldWithInteger(ui->mentalDrv, drvs.getMental());
    setFieldWithInteger(ui->magicalDrv, drvs.getMagical());

    setFieldWithInteger(ui->movementPointsAdjust, targetCaste.getMovementPoints());
    setFieldWithInteger(ui->magicResistance, targetCaste.getMagicResistance());
    setFieldWithInteger(ui->twoHandedAdjust, targetCaste.getTwoHandedAdjust());
    /// @todo implement startingAgeGroup and bonusAttacks fields
    setFieldWithInteger(ui->maxAttacksPerRound, targetCaste.getMaxAttacksPerRound());
    setFieldWithInteger(ui->maxStaminaBonus, std::abs(targetCaste.getMaxStaminaBonus()));
    auto setFieldWithBool = [](QLineEdit* le, bool value) { le->setText(value ? tr("Yes") : tr("No")); };
    setFieldWithBool(ui->canUseMissileWeapons, targetCaste.canUseMissileWeapons());
    setFieldWithBool(ui->getsMissileBonusDamage, targetCaste.getsMissileBonusDamage());

    const auto& sc = targetCaste.getSpellCasting();
    auto emitSpellClass = [setFieldWithInteger](QLineEdit* maxLevel, QLineEdit* startingAt, const realmz::SpellClassInfo& value) {
        if (value.isEnabled()) {
            setFieldWithInteger(maxLevel, value.getMaxLevelSpells());
            setFieldWithInteger(startingAt, value.getStartingLevel());
        } else {
            maxLevel->clear();
            startingAt->clear();
        }
    };
    emitSpellClass(ui->enchanterMaxLevelSpells, ui->enchanterStartingAtLevel, sc.getEnchanterInfo());
    emitSpellClass(ui->priestMaxLevelSpells, ui->priestStartingAtLevel, sc.getPriestInfo());
    emitSpellClass(ui->sorcererMaxLevel, ui->sorcererStartingLvl, sc.getSorcererInfo());
    switch (targetCaste.getAgeGroup()) {
        case realmz::AgeGroup::Youth:
            ui->startingAgeGroup->setText("Youth");
            break;
        case realmz::AgeGroup::Young:
            ui->startingAgeGroup->setText("Young");
            break;
        case realmz::AgeGroup::Prime:
            ui->startingAgeGroup->setText("Prime");
            break;
        case realmz::AgeGroup::Adult:
            ui->startingAgeGroup->setText("Adult");
            break;
        case realmz::AgeGroup::Senior:
            ui->startingAgeGroup->setText("Senior");
            break;
        default:
            ui->startingAgeGroup->setText("ERROR");
            break;
    }
    switch (targetCaste.getBonusAttacks()) {
        case realmz::BonusAttacksStyle::OneAndOneHalf:
            ui->bonusAttacks->setText("1 1/2");
            break;
        case realmz::BonusAttacksStyle::One:
            ui->bonusAttacks->setText("1");
            break;
        case realmz::BonusAttacksStyle::OneHalf:
            ui->bonusAttacks->setText("1/2");
            break;
        case realmz::BonusAttacksStyle::Two:
            ui->bonusAttacks->setText("2");
            break;
        default:
            ui->bonusAttacks->setText("None");
            break;
    }
}

void
CasteInfoPanel::on_casteSelector_activated(int index)
{
    ck = static_cast<realmz::CasteKind>(index);
    installCaste(realmz::loadCaste(ck));
}

void
CasteInfoPanel::addCondition(const QString &str, int atLevel)
{
    /// @todo implement
}
