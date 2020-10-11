#ifndef VIEWAGINGDIALOG_H
#define VIEWAGINGDIALOG_H

#include <QDialog>
#include "../RaceData.h"

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
    Ui::ViewAgingDialog *ui;
    realmz::RaceKind rd;

};

#endif // VIEWAGINGDIALOG_H
