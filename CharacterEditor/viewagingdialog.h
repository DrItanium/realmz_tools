#ifndef VIEWAGINGDIALOG_H
#define VIEWAGINGDIALOG_H

#include <QDialog>
#include "../RaceData.h"
#include "../AgeGroup.h"
#include <QAbstractTableModel>
#include "../CommonUIElements/ViewAgingTableModel.h"

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
private:
    void installRaceData();
private:
    Ui::ViewAgingDialog *ui;
    realmz::RaceKind rd = realmz::RaceKind::Human;
    std::unique_ptr<ViewAgingTableModel> vatm;
};

#endif // VIEWAGINGDIALOG_H
