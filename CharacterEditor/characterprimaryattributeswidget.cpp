#include "characterprimaryattributeswidget.h"
#include "ui_characterprimaryattributeswidget.h"
#include <QLineEdit>
#include <QString>

CharacterPrimaryAttributesWidget::CharacterPrimaryAttributesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CharacterPrimaryAttributesWidget)
{
    ui->setupUi(this);
}

CharacterPrimaryAttributesWidget::~CharacterPrimaryAttributesWidget()
{
    delete ui;
}
void
updateTriple(QLineEdit* min, QLineEdit* max, QLineEdit* adjust, const realmz::Attribute& attrib) {
    min->setText(QString::number(attrib.getMin()));
    max->setText(QString::number(attrib.getMax()));
    adjust->setText(QString::number(attrib.getAdjustment()));
}
void
CharacterPrimaryAttributesWidget::updateFields(realmz::Attributes attribs) {
    updateTriple(ui->agilityMin,ui->agilityMax, ui->agilityPlusMinus, attribs.getAgility());
    updateTriple(ui->brawnMin,ui->brawnMax, ui->brawnPlusMinus, attribs.getBrawn());
    updateTriple(ui->knowledgeMin,ui->knowledgeMax, ui->knowledgePlusMinus, attribs.getKnowledge());
    updateTriple(ui->judgmentMin,ui->judgmentMax, ui->judgmentPlusMinus, attribs.getJudgment());
    updateTriple(ui->luckMin,ui->luckMax, ui->luckPlusMinus, attribs.getLuck());
    updateTriple(ui->vitalityMin,ui->vitalityMax, ui->vitalityPlusMinus, attribs.getVitality());
}
