#ifndef VIEWAGINGDIALOG_H
#define VIEWAGINGDIALOG_H

#include <QDialog>
#include "../RaceData.h"
#include "../AgeGroup.h"

namespace Ui {
class ViewAgingDialog;
}

class ViewAgingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ViewAgingDialog(QWidget *parent = nullptr);
    ~ViewAgingDialog();
    void setRaceData(realmz::RaceKind nrd) noexcept;
signals:
    void update_Youth(realmz::AgeRange range, realmz::AgeModifiers mod);
    void update_Young(realmz::AgeRange range, realmz::AgeModifiers mod);
    void update_Adult(realmz::AgeRange range, realmz::AgeModifiers mod);
    void update_Prime(realmz::AgeRange range, realmz::AgeModifiers mod);
    void update_Senior(realmz::AgeRange range, realmz::AgeModifiers mod);
private:
    void installRaceData();
private:
    Ui::ViewAgingDialog *ui;
    realmz::RaceKind rd = realmz::RaceKind::Human;

};

#endif // VIEWAGINGDIALOG_H
