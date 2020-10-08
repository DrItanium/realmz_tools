#include "charactercombaticonview.h"
#include "ui_charactercombaticonview.h"

CharacterCombatIconView::CharacterCombatIconView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CharacterCombatIconView)
{
    ui->setupUi(this);
}

CharacterCombatIconView::~CharacterCombatIconView()
{
    delete ui;
}
