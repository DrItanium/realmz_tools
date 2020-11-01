#include "racestatsview.h"
#include "ui_racestatsview.h"
#include "../RaceData.h"
#include "viewagingdialog.h"

RaceStatsView::RaceStatsView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RaceStatsView)
{
    ui->setupUi(this);
    installRace(realmz::loadRaceData(rk));
}

RaceStatsView::~RaceStatsView()
{
    delete ui;
}

void RaceStatsView::on_viewAgingButton_clicked()
{
   ViewAgingDialog vad(this);
   vad.setRaceData(rk);
   vad.exec();
}

void
RaceStatsView::on_raceSelect_activated(int index)
{
    /// @todo implement
    this->rk = static_cast<realmz::RaceKind>(index + 1);
    /// @todo load the corresponding race info using loadrace
    installRace(realmz::loadRaceData(rk));
}

void
RaceStatsView::installRace(const realmz::RaceData &targetRace)
{
    emit updateCoreStats(targetRace.getAttributes());

    auto setSpecialAttribute = [](auto* result, const realmz::Ability& ability) {
        result->setText(QString::number(ability.getInitial()));
    };
    auto setField = [](auto* result, int value) {
        result->setText(QString::number(value));
    };
    const auto& sas = targetRace.getSpecialAbilities();
    setSpecialAttribute(ui->sneakAttackField, sas.getSneakAttack());
    setSpecialAttribute(ui->causeMajorWoundField, sas.getMajorWound());
    setSpecialAttribute(ui->detectSecretField, sas.getDetectSecret());
    setSpecialAttribute(ui->detectTrapField, sas.getDetectTrap());
    setSpecialAttribute(ui->acrobaticActField, sas.getAcrobaticAct());
    setSpecialAttribute(ui->disableTrapField, sas.getDisableTrap());
    setSpecialAttribute(ui->forceLockField, sas.getForceLock());
    setSpecialAttribute(ui->pickLockField, sas.getPickLock());
    setSpecialAttribute(ui->turnUndeadField, sas.getTurnUndead());
    setField(ui->twoHandedAdjust, targetRace.getTwoHandedAdjustment());
    setField(ui->attacksPerRound, targetRace.getAttacksPerRound());
    ui->raceCanRegenerate->setText(targetRace.canRegenerate() ? tr("Yes") : tr("No"));
    setField(ui->magicResistance, targetRace.getMagicResistance());
    setField(ui->missileWeaponAdjust, targetRace.getMissileWeaponAdjust());
    setField(ui->baseMovementPoints, targetRace.getBaseMovementPoints());
    setField(ui->maxAttacksPerRound, targetRace.getMaxAttacksPerRound());

    emit updateDRVs(targetRace.getDrvs());

    const auto& hatred = targetRace.getRaceHatredStats();
    setField(ui->hitMagicUsing, hatred.getHitVsMagicUsing());
    setField(ui->plusDemonic, hatred.getHitVsDemonic());
    setField(ui->plusGiantSize, hatred.getHitGiantSize());
    setField(ui->plusIntelligent, hatred.getHitVsIntelligent());
    setField(ui->plusNonHumanoid, hatred.getHitNonHumanoid());
    setField(ui->plusReptilian, hatred.getHitVsReptilian());
    setField(ui->plusUndead, hatred.getHitVsUndead());
    setField(ui->plusVeryEvil, hatred.getHitVsVeryEvil());
}
