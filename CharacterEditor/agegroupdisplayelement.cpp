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
}
