#ifndef RACESTATSVIEW_H
#define RACESTATSVIEW_H

#include <QWidget>

namespace Ui {
class RaceStatsView;
}

class RaceStatsView : public QWidget
{
    Q_OBJECT

public:
    explicit RaceStatsView(QWidget *parent = nullptr);
    ~RaceStatsView();
signals:
    void onNextPressed();
    void onViewAgingPressed();
private slots:
    void on_selector_activated(int index);
    void on_viewAgingButton_clicked();

    void on_raceSelect_activated(int index);

    void on_nextButton_clicked();

private:
    Ui::RaceStatsView *ui;
};

#endif // RACESTATSVIEW_H
