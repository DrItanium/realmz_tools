#ifndef CASTEINFOPANEL_H
#define CASTEINFOPANEL_H

#include <QWidget>
#include <QString>
#include "../Caste.h"
#include <tuple>
#include <list>

namespace Ui {
class CasteInfoPanel;
}

class CasteInfoPanel : public QWidget
{
    Q_OBJECT

public:
    explicit CasteInfoPanel(QWidget *parent = nullptr);
    ~CasteInfoPanel();
signals:
    void onNextPressed();
private slots:
    void on_casteSelector_activated(int index);
    void on_nextButton_clicked();
private:
    void installCaste(const realmz::Caste& targetCaste);
    void addCondition(const QString& str, int atLevel);
private:
    Ui::CasteInfoPanel *ui;
    std::list<std::tuple<QString, int>> conditions;
};

#endif // CASTEINFOPANEL_H
