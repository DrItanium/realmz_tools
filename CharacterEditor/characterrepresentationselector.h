#ifndef CHARACTERPORTRAITSELECTOR_H
#define CHARACTERPORTRAITSELECTOR_H

#include <QDialog>
#include <QAbstractTableModel>
#include "../CommonUIElements/RepresentationModel.h"

namespace Ui {
class CharacterRepresentationSelector;
}

class CharacterRepresentationSelector : public QDialog
{
    Q_OBJECT
public slots:
    void setTargetRepresentation(QModelIndex qmi);
public:
    explicit CharacterRepresentationSelector(QWidget *parent = nullptr);
    ~CharacterRepresentationSelector();
    void setModel(RepresentationModel* theModel) noexcept;
    [[nodiscard]] constexpr auto getSelectedRepresentation() const noexcept { return targetRepresentation; }
private:
    Ui::CharacterRepresentationSelector *ui;
    RepresentationModel* _rmi = nullptr;
    int targetRepresentation = 0;
};

#endif // CHARACTERPORTRAITSELECTOR_H
