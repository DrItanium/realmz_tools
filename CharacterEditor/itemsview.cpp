#include "itemsview.h"
#include "ui_itemsview.h"

ItemsView::ItemsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemsView)
{
    ui->setupUi(this);
}

ItemsView::~ItemsView()
{
    delete ui;
}
