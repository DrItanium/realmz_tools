#ifndef CASTEINFOPANEL_H
#define CASTEINFOPANEL_H

#include <QDialog>
#include <QString>
#include <tuple>
#include <list>
#include <QDialog>
#include "../Caste.h"

namespace Ui {
class CasteInfoPanel;
}

class CasteInfoPanel : public QDialog
{
    Q_OBJECT

public:
    explicit CasteInfoPanel(QWidget *parent = nullptr);
    ~CasteInfoPanel();
private slots:
    void on_casteSelector_activated(int index);
signals:
    void updateCoreStats(realmz::Attributes);
    void updateDRVs(realmz::DRVAdjustments);
public:
    constexpr realmz::CasteKind getSelectedCasteKind() const noexcept { return ck; }
private:
    void installCaste(const realmz::Caste& targetCaste);
    void addCondition(const QString& str, int atLevel);
private:
    Ui::CasteInfoPanel *ui;
    std::list<std::tuple<QString, int>> conditions;
    realmz::CasteKind ck = realmz::CasteKind::Fighter;
};

#endif // CASTEINFOPANEL_H
