#include "abilitiesview.h"
#include "ui_abilitiesview.h"

AbilitiesView::AbilitiesView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AbilitiesView)
{
    ui->setupUi(this);
}

AbilitiesView::~AbilitiesView()
{
    delete ui;
}
