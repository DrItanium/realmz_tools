#include "casteinfopanel.h"
#include "ui_casteinfopanel.h"

CasteInfoPanel::CasteInfoPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CasteInfoPanel)
{
    ui->setupUi(this);
}

CasteInfoPanel::~CasteInfoPanel()
{
    delete ui;
}
