#include "casteinfopanel.h"
#include "ui_casteinfopanel.h"
#include "../Caste.h"

CasteInfoPanel::CasteInfoPanel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CasteInfoPanel)
{
    ui->setupUi(this);
    // on initialization we have to force the fighter data
}

CasteInfoPanel::~CasteInfoPanel()
{
    delete ui;
}

void
CasteInfoPanel::installCaste(const realmz::Caste &targetCaste)
{
}

void
CasteInfoPanel::on_casteSelector_activated(int index)
{
        ck = static_cast<realmz::CasteKind>(index);
        // 1) We call the global method getCaste(ck) which will acquire the given caste
        // we then "install" that caste into the view
}

void
CasteInfoPanel::on_nextButton_clicked()
{
        // call done
    done(QDialog::Accepted);
}

void
CasteInfoPanel::addCondition(const QString &str, int atLevel)
{
    /// @todo implement
}

