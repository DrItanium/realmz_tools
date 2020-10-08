#ifndef CHARACTERCOMBATICONVIEW_H
#define CHARACTERCOMBATICONVIEW_H

#include <QWidget>

namespace Ui {
class CharacterCombatIconView;
}

class CharacterCombatIconView : public QWidget
{
    Q_OBJECT

public:
    explicit CharacterCombatIconView(QWidget *parent = nullptr);
    ~CharacterCombatIconView();

private:
    Ui::CharacterCombatIconView *ui;
};

#endif // CHARACTERCOMBATICONVIEW_H
