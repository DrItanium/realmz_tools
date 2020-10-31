#ifndef CHARACTERPORTRAITSELECTOR_H
#define CHARACTERPORTRAITSELECTOR_H

#include <QDialog>

namespace Ui {
class CharacterPortraitSelector;
}

class CharacterPortraitSelector : public QDialog
{
    Q_OBJECT

public:
    explicit CharacterPortraitSelector(QWidget *parent = nullptr);
    ~CharacterPortraitSelector();

private:
    Ui::CharacterPortraitSelector *ui;
};

#endif // CHARACTERPORTRAITSELECTOR_H
