#ifndef RACESTATSVIEW_H
#define RACESTATSVIEW_H

#include <QDialog>
#include "../RaceData.h"

namespace Ui {
class RaceStatsView;
}

class RaceStatsView : public QDialog
{
    Q_OBJECT

public:
    explicit RaceStatsView(QWidget *parent = nullptr);
    ~RaceStatsView();
signals:
    void updateCoreStats(realmz::Attributes);
    void updateDRVs(realmz::DRVAdjustments);
private slots:
    void on_viewAgingButton_clicked();

    void on_raceSelect_activated(int index);
private:
    void installRace(const realmz::RaceData& targetRace);
public:
    constexpr auto getSelectedRaceKind() const noexcept { return rk; }

private:
    Ui::RaceStatsView *ui;
    realmz::RaceKind rk = realmz::RaceKind::Human;
};

#endif // RACESTATSVIEW_H
