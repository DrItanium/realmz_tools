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
    void setRaceData(const realmz::RaceData& nrd);
private:
    Ui::ViewAgingDialog *ui;
    realmz::RaceData rd;

};

#endif // VIEWAGINGDIALOG_H
