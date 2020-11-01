#include "viewagingdialog.h"
#include "ui_viewagingdialog.h"

ViewAgingDialog::ViewAgingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewAgingDialog),
    vatm(new ViewAgingTableModel(this))
{
        ui->setupUi(this);
        ui->tableView->setModel(vatm.get());
}

ViewAgingDialog::~ViewAgingDialog()
{
        delete ui;
}

void
ViewAgingDialog::setRaceData(realmz::RaceKind nrd) noexcept
{
        rd = nrd;
        vatm->setRaceKind(nrd);
        installRaceData();
}

void
ViewAgingDialog::installRaceData() {

#if 0
        auto emitTarget = [this, &targetData](realmz::AgeGroup g) {
                const auto& ar = targetData.getAgeRange(g);
                const auto& am = targetData.getAgeModifier(g);
                switch (g) {
                case realmz::AgeGroup::Adult: emit update_Adult(ar, am); break;
                case realmz::AgeGroup::Youth: emit update_Youth(ar, am); break;
                case realmz::AgeGroup::Young: emit update_Young(ar, am); break;
                case realmz::AgeGroup::Senior: emit update_Senior(ar, am); break;
                case realmz::AgeGroup::Prime: emit update_Prime(ar, am); break;
                default: break;
                }
        };
        emitTarget(realmz::AgeGroup::Youth);
        emitTarget(realmz::AgeGroup::Young);
        emitTarget(realmz::AgeGroup::Adult);
        emitTarget(realmz::AgeGroup::Prime);
        emitTarget(realmz::AgeGroup::Senior);
#endif
}
