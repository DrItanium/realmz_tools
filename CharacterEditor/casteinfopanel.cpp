#include <QLineEdit>
#include "casteinfopanel.h"
#include "ui_casteinfopanel.h"
#include "../Caste.h"

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
    auto setCoreAttribute = [](QLineEdit* min, QLineEdit* max, QLineEdit* adjust, const realmz::Attribute& attr) {
        min->setText(QString::number(attr.getMin()));
        max->setText(QString::number(attr.getMax()));
        adjust->setText(QString::number(attr.getAdjustment()));
    };
    const auto& attr = targetCaste.getAttributes();
    setCoreAttribute(ui->agilityMin, ui->agilityMax, ui->agilityPlusMinus, attr.getAgility());
    setCoreAttribute(ui->brawnMin, ui->brawnMax, ui->brawnPlusMinus, attr.getBrawn());
    setCoreAttribute(ui->knowledgeMin, ui->knowledgeMax, ui->knowledgePlusMinus, attr.getKnowledge());
    setCoreAttribute(ui->judgmentMin, ui->judgmentMax, ui->judgmentPlusMinus, attr.getJudgment());
    setCoreAttribute(ui->vitalityMin, ui->vitalityMax, ui->vitalityPlusMinus, attr.getVitality());
    setCoreAttribute(ui->luckMin, ui->luckMax, ui->luckPlusMinus, attr.getLuck());

    auto setInitialAndLevelUp = [](QLineEdit* initial, QLineEdit* lvlUp, const realmz::Ability& ability) {
        initial->setText(QString::number(ability.getInitial()));
        lvlUp->setText(QString::number(ability.getLevelUp()));
    };
    setInitialAndLevelUp(ui->sneakInitial, ui->sneakLvlUp, targetCaste.getInitialAbilities()._sneakAttack);
    setInitialAndLevelUp(ui->majorWoundInitial, ui->majorWoundLvlUp, targetCaste.getInitialAbilities()._majorWound);
    setInitialAndLevelUp(ui->detectSecretInitial, ui->detectSecretLvlUp, targetCaste.getInitialAbilities()._detectSecret);
    setInitialAndLevelUp(ui->acrobaticActInitial, ui->acrobaticActLvlUp, targetCaste.getInitialAbilities()._acrobaticAct);
    setInitialAndLevelUp(ui->detectTrapInitial, ui->detectTrapLvlUp, targetCaste.getInitialAbilities()._detectTrap);
    setInitialAndLevelUp(ui->disableTrapInitial, ui->disableTrapLvlUp, targetCaste.getInitialAbilities()._disableTrap);
    setInitialAndLevelUp(ui->forceLockInitial, ui->forceLockLvlUp, targetCaste.getInitialAbilities()._forceLock);
    setInitialAndLevelUp(ui->pickLockInitial, ui->pickLockLvlUp, targetCaste.getInitialAbilities()._pickLock);
    setInitialAndLevelUp(ui->turnUndead, ui->turnUndeadLvlUp, targetCaste.getInitialAbilities()._turnUndead);
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
    if (sc.supportsEnchanterSpellClass()) {
        setFieldWithInteger(ui->enchanterMaxLevelSpells, sc.getEnchanterInfo().getMaxLevelSpells());
        setFieldWithInteger(ui->enchanterStartingAtLevel, sc.getEnchanterInfo().getStartingLevel());
    } else {
        ui->enchanterMaxLevelSpells->clear();
        ui->enchanterStartingAtLevel->clear();
    }
    if (sc.supportsPriestSpellClass()) {
        setFieldWithInteger(ui->priestMaxLevelSpells, sc.getPriestInfo().getMaxLevelSpells());
        setFieldWithInteger(ui->priestStartingAtLevel, sc.getPriestInfo().getStartingLevel());
    } else {
        ui->priestMaxLevelSpells->clear();
        ui->priestStartingAtLevel->clear();

    }

    if (sc.supportsSorcererSpellClass()) {
        setFieldWithInteger(ui->sorcererMaxLevel, sc.getSorcererInfo().getMaxLevelSpells());
        setFieldWithInteger(ui->sorcererStartingLvl, sc.getSorcererInfo().getStartingLevel());
    } else {
        ui->sorcererMaxLevel->clear();
        ui->sorcererStartingLvl->clear();
    }
}

void
CasteInfoPanel::on_casteSelector_activated(int index)
{
    ck = static_cast<realmz::CasteKind>(index);
    installCaste(realmz::loadCaste(ck));
}

void
CasteInfoPanel::on_nextButton_clicked()
{
    // call done
    done(QDialog::Accepted);
}

void
CasteInfoPanel::addCondition(const QString &str, int atLevel)
{
    /// @todo implement
}

