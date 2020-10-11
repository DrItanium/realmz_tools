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
private slots:
    void on_selector_activated(int index);
    void on_viewAgingButton_clicked();

    void on_raceSelect_activated(int index);

    void on_nextButton_clicked();
public:
    constexpr auto getSelectedRaceKind() const noexcept { return rk; }

private:
    Ui::RaceStatsView *ui;
    realmz::RaceKind rk = realmz::RaceKind::Human;
};

#endif // RACESTATSVIEW_H
