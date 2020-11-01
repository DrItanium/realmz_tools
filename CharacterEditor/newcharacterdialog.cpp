#include "newcharacterdialog.h"
#include "ui_newcharacterdialog.h"

NewCharacterDialog::NewCharacterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewCharacterDialog)
{
    ui->setupUi(this);
}

NewCharacterDialog::~NewCharacterDialog()
{
    delete ui;
}

void NewCharacterDialog::on_reroll_clicked()
{

}

void NewCharacterDialog::on_viewAging_clicked()
{

}

void NewCharacterDialog::on_lineEdit_returnPressed()
{

}
