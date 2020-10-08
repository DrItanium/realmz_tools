#include "iconselect6.h"
#include "ui_iconselect6.h"

IconSelect6::IconSelect6(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IconSelect6)
{
    ui->setupUi(this);
}

IconSelect6::~IconSelect6()
{
    delete ui;
}
