#ifndef CHARACTERPRIMARYSTATVIEW_H
#define CHARACTERPRIMARYSTATVIEW_H

#include <QWidget>
#include <QString>
namespace Ui {
class CharacterPrimaryStatView;
}

class CharacterPrimaryStatView : public QWidget
{
    Q_OBJECT
public:
    explicit CharacterPrimaryStatView(QWidget *parent = nullptr);
    ~CharacterPrimaryStatView();
signals:
#define X(field) \
    void update ## field (QString); \
    void on ## field ## Modified (QString)
    X(Brawn);
    X(Name);
    X(SpellSelectionPoints);
    X(Knowledge);
    X(Judgment);
    X(Agility);
    X(Vitality);
    X(Luck);
    X(Skill);
    X(Age);
#undef X
    void updateAttackBonus(QString);
    void updateDefenseBonus(QString);
public slots:
#define X(field) \
    void field ## Updated (QString)
    X(name);
    X(brawn);
    X(knowledge);
    X(judgment);
    X(agility);
    X(vitality);
    X(luck);
    X(age);
#undef X
public slots:
    void updateBasicStats(QString name, int brawn, int knowledge, int judgment, int agility, int vitality, int luck);
    void updateAge(int age);
    void addCondition(QString text);
    void addSpecialAbility(QString text);
    void clearConditionList();
    void clearSpecialAbilityList();
    void removeCondition(QString text);
    void removeSpecialAbility(QString text);

    void updateSkillLevel(int skillLevel);
    void updateDamageReductionVs(int charm, int heat, int cold, int electric, int chemical, int mental, int magic, int special);
    void updateVictoryPoints(int value);
    void updateMovementBonus(int value);
    void updateDamagePlus(int value);
    void updateChanceToHit(int value);
    void updateSpellPoints(int current, int total);
    void updateStaminaPoints(int current, int total);
    void updateArmorRating(int value);
    void updateMagicResistance(int value);
    void updateBooty(int gold, int gems, int jewelry);
    void updateHandToHandRelatedDamages(int bareHand, int handToHand);
    void updateMissilePercentages(int adjust, int dodge);

private:
    Ui::CharacterPrimaryStatView *ui;
};

#endif // CHARACTERPRIMARYSTATVIEW_H
