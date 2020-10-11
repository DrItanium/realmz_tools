#include "viewagingdialog.h"
#include "ui_viewagingdialog.h"

ViewAgingDialog::ViewAgingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewAgingDialog)
{
    ui->setupUi(this);
}

ViewAgingDialog::~ViewAgingDialog()
{
    delete ui;
}

void
ViewAgingDialog::setRaceData(realmz::RaceKind nrd) noexcept
{
    rd = nrd;
}