#include "characterprimarystatview.h"
#include "ui_characterprimarystatview.h"

CharacterPrimaryStatView::CharacterPrimaryStatView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CharacterPrimaryStatView)
{
    ui->setupUi(this);
}

CharacterPrimaryStatView::~CharacterPrimaryStatView()
{
    delete ui;
}

void
CharacterPrimaryStatView::nameUpdated(QString str) {
    // use it for pure forwarding capabilities right now
    emit onNameModified(str);
}
#define X(field, capped) \
    void CharacterPrimaryStatView:: field ## Updated (QString str) {  emit on ## capped ## Modified ( str ); }
X(brawn, Brawn);
X(age, Age);
X(knowledge, Knowledge);
X(judgment, Judgment);
X(agility, Agility);
X(luck, Luck);
X(vitality, Vitality);
#undef X
void
CharacterPrimaryStatView::updateBasicStats(QString name, int brawn, int knowledge, int judgment, int agility, int vitality, int luck) {
    emit updateName(name);
    QString tmp;
    tmp.setNum(brawn);
    /// @todo convert integers to string
    emit updateBrawn(tmp);
    tmp.setNum(knowledge);
    emit updateKnowledge(tmp);
    tmp.setNum(judgment);
    emit updateJudgment(tmp);
    tmp.setNum(agility);
    emit updateAgility(tmp);
    tmp.setNum(vitality);
    emit updateVitality(tmp);
    tmp.setNum(luck);
    emit updateLuck(tmp);
}

void
CharacterPrimaryStatView::updateAge(int age) {
    QString tmp;
    tmp.setNum(age);
    emit updateAge(tmp);
}

void
CharacterPrimaryStatView::addCondition(QString text) {
    // there is no slot for this so I have to do it manually
    this->ui->conditionsItemList->addItem(text);
}

void
CharacterPrimaryStatView::addSpecialAbility(QString text) {
    this->ui->specialAbilitiesList->addItem(text);
}

void CharacterPrimaryStatView::clearConditionList(){}
void CharacterPrimaryStatView::clearSpecialAbilityList(){}
void CharacterPrimaryStatView::removeCondition(QString text){}
void CharacterPrimaryStatView::removeSpecialAbility(QString text){}
void CharacterPrimaryStatView::updateSkillLevel(int skillLevel){}
void CharacterPrimaryStatView::updateDamageReductionVs(int charm, int heat, int cold, int electric, int chemical, int mental, int magic, int special){}
void CharacterPrimaryStatView::updateVictoryPoints(int value){}
void CharacterPrimaryStatView::updateMovementBonus(int value){}
void CharacterPrimaryStatView::updateDamagePlus(int value){}
void CharacterPrimaryStatView::updateChanceToHit(int value){}
void CharacterPrimaryStatView::updateSpellPoints(int current, int total){}
void CharacterPrimaryStatView::updateStaminaPoints(int current, int total){}
void CharacterPrimaryStatView::updateArmorRating(int value){}
void CharacterPrimaryStatView::updateMagicResistance(int value){}
void CharacterPrimaryStatView::updateBooty(int gold, int gems, int jewelry){}
void CharacterPrimaryStatView::updateHandToHandRelatedDamages(int bareHand, int handToHand){}
void CharacterPrimaryStatView::updateMissilePercentages(int adjust, int dodge){}
