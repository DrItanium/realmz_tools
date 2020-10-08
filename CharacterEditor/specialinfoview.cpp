#include "specialinfoview.h"
#include "ui_specialinfoview.h"

SpecialInfoView::SpecialInfoView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpecialInfoView)
{
    ui->setupUi(this);
}

SpecialInfoView::~SpecialInfoView()
{
    delete ui;
}
