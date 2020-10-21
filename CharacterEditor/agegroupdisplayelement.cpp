#include "agegroupdisplayelement.h"
#include "ui_agegroupdisplayelement.h"

AgeGroupDisplayElement::AgeGroupDisplayElement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AgeGroupDisplayElement)
{
    ui->setupUi(this);
}

AgeGroupDisplayElement::~AgeGroupDisplayElement()
{
    delete ui;
}
void
AgeGroupDisplayElement::updateFields(realmz::AgeRange range, realmz::AgeModifiers mods) {
    setAgeModifier(mods);
    setAgeRange(range);
}
void
AgeGroupDisplayElement::setAgeRange(const realmz::AgeRange& range) {
        ui->ageFrom->setText(QString::number(range.getFrom()));
        ui->ageTo->setText(QString::number(range.getTo()));
}

void
AgeGroupDisplayElement::setAgeModifier(const realmz::AgeModifiers& modifier) {
    auto updateField = [](auto* element, int value) noexcept {
        if (value == 0) {
            element->clear();
        } else {
            element->setText(QString::number(value));
        }
    };
    updateField(ui->agility, modifier.getAgility());
    updateField(ui->brawn, modifier.getBrawn());
    updateField(ui->charm, modifier.getCharm());
    updateField(ui->chemical, modifier.getChemical());
    updateField(ui->cold, modifier.getCold());
    updateField(ui->electricalDrv, modifier.getElectrical());
    updateField(ui->heat, modifier.getHeat());
    updateField(ui->judgment, modifier.getJudgment());
    updateField(ui->knowledge, modifier.getKnowledge());
    updateField(ui->luck, modifier.getLuck());
    updateField(ui->magicResist, modifier.getMagicResist());
    updateField(ui->mental, modifier.getMental());
    updateField(ui->movement, modifier.getMovement());
    updateField(ui->magical, modifier.getMagical());
    updateField(ui->vitality, modifier.getVitality());
}
