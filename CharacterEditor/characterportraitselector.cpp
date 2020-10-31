#include "characterportraitselector.h"
#include "ui_characterportraitselector.h"

CharacterPortraitSelector::CharacterPortraitSelector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CharacterPortraitSelector)
{
    ui->setupUi(this);
}

CharacterPortraitSelector::~CharacterPortraitSelector()
{
    delete ui;
}
