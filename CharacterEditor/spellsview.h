#ifndef SPELLSVIEW_H
#define SPELLSVIEW_H

#include <QWidget>

namespace Ui {
class SpellsView;
}

class SpellsView : public QWidget
{
    Q_OBJECT

public:
    explicit SpellsView(QWidget *parent = nullptr);
    ~SpellsView();
private slots:
    void on_s0_toggled(bool checked);

private:
    Ui::SpellsView *ui;
};

#endif // SPELLSVIEW_H
