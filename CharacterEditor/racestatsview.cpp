#include "racestatsview.h"
#include "ui_racestatsview.h"
#include "../RaceData.h"
#include "viewagingdialog.h"

RaceStatsView::RaceStatsView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RaceStatsView)
{
    ui->setupUi(this);
}

RaceStatsView::~RaceStatsView()
{
    delete ui;
}

void RaceStatsView::on_viewAgingButton_clicked()
{
   ViewAgingDialog vad(this);
   //vad.setRaceData();
   vad.exec();
}

void
RaceStatsView::on_raceSelect_activated(int index)
{
    /// @todo implement
    this->rk = static_cast<realmz::RaceKind>(index);
    /// @todo load the corresponding race info using loadrace
}

void
RaceStatsView::on_nextButton_clicked()
{
    done(QDialog::Accepted);
}

