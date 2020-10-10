#ifndef RACESTATSVIEW_H
#define RACESTATSVIEW_H

#include <QWidget>

namespace Ui {
class RaceStatsView;
}

class RaceStatsView : public QWidget
{
    Q_OBJECT

public:
    explicit RaceStatsView(QWidget *parent = nullptr);
    ~RaceStatsView();
public slots:
    void addCondition(QString cond) ;
    void setSneakAttack(int value);
    void setCauseMajorWound(int value);
    void setDetectSecret(int value);
    void setAcrobaticAct(int value);
    void setDetectTrap(int value);
    void setDisableTrap(int value);
    void setForceLock(int value);
    void setPickLock(int value);
    void setTurnUndead(int value);
    void setBrawnAttribute(int min, int max, int plusMinus);
    void setKnowledgeAttribute(int min, int max, int plusMinus);
    void setJudgmentAttribute(int min, int max, int plusMinus);
    void setAgilityAttribute(int min, int max, int plusMinus);
    void setVitalityAttribute(int min, int max, int plusMinus);
    void setLuckAttribute(int min, int max, int plusMinus);

    void setDRVCharm(int value);
    void setDRVHeat(int value);
    void setDRVCold(int value);
    void setDRVElectric(int value);
    void setDRVChemical(int value);
    void setDRVMental(int value);
    void setDRVMagical(int value);

    void setBaseMovementPoints(int value);
    void setMagicResistance(int value);
    void setTwoHandedAdjustment(int value);
    void setMissileWeaponAdjust(int value);
    void setRaceCanRegenerate(bool value);
    void setAttacksPerRound(int attacks, int numRounds);
    void setMaxAttacksPerRound(int value);

    void setPlusToHitMagicUsing(int value);
    void setPlusToHitUndead(int value);
    void setPlusToHitDemonicDevil(int value);
    void setPlusToHitReptilian(int value);
    void setPlusToHitVeryEvil(int value);
    void setPlusToHitIntelligent(int value);
    void setPlusToHitGiantSize(int value);
    void setPlusToHitNonHumanoid(int value);
private:
    Ui::RaceStatsView *ui;
};

#endif // RACESTATSVIEW_H
