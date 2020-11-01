#include "characterrepresentationselector.h"
#include "ui_characterrepresentationselector.h"
#include <QException>

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
CharacterRepresentationSelector::setModel(RepresentationModel* theModel) noexcept {
    ui->tableView->setModel(theModel);
    _rmi = theModel;
}

void
CharacterRepresentationSelector::setTargetRepresentation(QModelIndex qmi) {
    if (_rmi == nullptr) {
        throw "model not set";
    }
    targetRepresentation = _rmi->computeProperIndex(qmi.row(), qmi.column());
}