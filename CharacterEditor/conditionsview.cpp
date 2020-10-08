#include "conditionsview.h"
#include "ui_conditionsview.h"

ConditionsView::ConditionsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConditionsView)
{
    ui->setupUi(this);
}

ConditionsView::~ConditionsView()
{
    delete ui;
}
