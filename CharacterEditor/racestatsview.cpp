#include "racestatsview.h"
#include "ui_racestatsview.h"
#include "../RaceData.h"

RaceStatsView::RaceStatsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RaceStatsView)
{
    ui->setupUi(this);
}

RaceStatsView::~RaceStatsView()
{
    delete ui;
}

void RaceStatsView::addCondition(QString cond) {

}

void RaceStatsView::on_viewAgingButton_clicked()
{
   emit onViewAgingPressed();
}

void
RaceStatsView::on_raceSelect_activated(int index)
{
    /// @todo implement

}

void
RaceStatsView::on_nextButton_clicked()
{
   emit onNextPressed();
}
