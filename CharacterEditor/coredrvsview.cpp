#include "coredrvsview.h"
#include "ui_coredrvsview.h"

CoreDRVsView::CoreDRVsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CoreDRVsView)
{
    ui->setupUi(this);
}

CoreDRVsView::~CoreDRVsView()
{
    delete ui;
}

void
CoreDRVsView::populate(realmz::DRVAdjustments adj) {
    auto setEntry = [](auto thingy, int value) { thingy->setText(QString::number(value)); };
    setEntry(ui->charmDRV, adj.getCharm());
    setEntry(ui->magicalDRV, adj.getMagical());
    setEntry(ui->mentalDRV, adj.getMental());
    setEntry(ui->chemicalDRV, adj.getChemical());
    setEntry(ui->electricDRV, adj.getElectric());
    setEntry(ui->coldDRV, adj.getCold());
    setEntry(ui->heatDRV, adj.getHeat());
}
