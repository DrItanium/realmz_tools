#ifndef CHARACTERPORTRAITSELECTOR_H
#define CHARACTERPORTRAITSELECTOR_H

#include <QDialog>
#include <QAbstractTableModel>

namespace Ui {
class CharacterRepresentationSelector;
}

class CharacterRepresentationSelector : public QDialog
{
    Q_OBJECT

public:
    explicit CharacterRepresentationSelector(QWidget *parent = nullptr);
    ~CharacterRepresentationSelector();
    void setModel(QAbstractTableModel* theModel) noexcept;
private:
    Ui::CharacterRepresentationSelector *ui;
};

#endif // CHARACTERPORTRAITSELECTOR_H
