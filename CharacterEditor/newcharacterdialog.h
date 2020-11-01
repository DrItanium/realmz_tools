#ifndef NEWCHARACTERDIALOG_H
#define NEWCHARACTERDIALOG_H

#include <QDialog>

namespace Ui {
class NewCharacterDialog;
}

class NewCharacterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewCharacterDialog(QWidget *parent = nullptr);
    ~NewCharacterDialog();

private slots:
    void on_reroll_clicked();

    void on_viewAging_clicked();

    void on_lineEdit_returnPressed();

private:
    Ui::NewCharacterDialog *ui;
};

#endif // NEWCHARACTERDIALOG_H
