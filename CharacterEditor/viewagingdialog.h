#ifndef VIEWAGINGDIALOG_H
#define VIEWAGINGDIALOG_H

#include <QDialog>

namespace Ui {
class ViewAgingDialog;
}

class ViewAgingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ViewAgingDialog(QWidget *parent = nullptr);
    ~ViewAgingDialog();

private:
    Ui::ViewAgingDialog *ui;
};

#endif // VIEWAGINGDIALOG_H
