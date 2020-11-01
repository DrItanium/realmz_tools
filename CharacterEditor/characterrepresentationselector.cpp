#include "characterrepresentationselector.h"
#include "ui_characterrepresentationselector.h"

CharacterRepresentationSelector::CharacterRepresentationSelector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CharacterRepresentationSelector)
{
    ui->setupUi(this);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
}

CharacterRepresentationSelector::~CharacterRepresentationSelector()
{
    delete ui;
}

void
CharacterRepresentationSelector::setModel(QAbstractTableModel *theModel) noexcept {
    ui->tableView->setModel(theModel);
}