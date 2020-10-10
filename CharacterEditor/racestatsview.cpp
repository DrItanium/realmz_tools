#include "racestatsview.h"
#include "ui_racestatsview.h"

RaceStatsView::RaceStatsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RaceStatsView)
{
    ui->setupUi(this);
}

RaceStatsView::~RaceStatsView()
{
    delete ui;
}

void RaceStatsView::addCondition(QString cond) {

}
void RaceStatsView::setSneakAttack(int value){
}
void RaceStatsView::setCauseMajorWound(int value){
}
void RaceStatsView::setDetectSecret(int value){
}
void RaceStatsView::setAcrobaticAct(int value){
}
void RaceStatsView::setDetectTrap(int value){
}
void RaceStatsView::setDisableTrap(int value){
}
void RaceStatsView::setForceLock(int value){
}
void RaceStatsView::setPickLock(int value){
}
void RaceStatsView::setTurnUndead(int value){
}
void RaceStatsView::setBrawnAttribute(int min, int max, int plusMinus){
}
void RaceStatsView::setKnowledgeAttribute(int min, int max, int plusMinus){
}
void RaceStatsView::setJudgmentAttribute(int min, int max, int plusMinus){
}
void RaceStatsView::setAgilityAttribute(int min, int max, int plusMinus){
}
void RaceStatsView::setVitalityAttribute(int min, int max, int plusMinus){
}
void RaceStatsView::setLuckAttribute(int min, int max, int plusMinus){
}
void RaceStatsView::setDRVCharm(int value){
}
void RaceStatsView::setDRVHeat(int value){
}
void RaceStatsView::setDRVCold(int value){
}
void RaceStatsView::setDRVElectric(int value){
}
void RaceStatsView::setDRVChemical(int value){
}
void RaceStatsView::setDRVMental(int value){
}
void RaceStatsView::setDRVMagical(int value){
}
void RaceStatsView::setBaseMovementPoints(int value){
}
void RaceStatsView::setMagicResistance(int value){
}
void RaceStatsView::setTwoHandedAdjustment(int value){
}
void RaceStatsView::setMissileWeaponAdjust(int value){
}
void RaceStatsView::setRaceCanRegenerate(bool value){
}
void RaceStatsView::setAttacksPerRound(int attacks, int numRounds){
}
void RaceStatsView::setMaxAttacksPerRound(int value){
}
void RaceStatsView::setPlusToHitMagicUsing(int value){
}
void RaceStatsView::setPlusToHitUndead(int value){
}
void RaceStatsView::setPlusToHitDemonicDevil(int value){
}
void RaceStatsView::setPlusToHitReptilian(int value){
}
void RaceStatsView::setPlusToHitVeryEvil(int value){
}
void RaceStatsView::setPlusToHitIntelligent(int value){
}
void RaceStatsView::setPlusToHitGiantSize(int value){
}
void RaceStatsView::setPlusToHitNonHumanoid(int value){
}
