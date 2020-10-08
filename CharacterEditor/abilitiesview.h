#ifndef ABILITIESVIEW_H
#define ABILITIESVIEW_H

#include <QWidget>

namespace Ui {
class AbilitiesView;
}

class AbilitiesView : public QWidget
{
    Q_OBJECT

public:
    explicit AbilitiesView(QWidget *parent = nullptr);
    ~AbilitiesView();

private:
    Ui::AbilitiesView *ui;
};

#endif // ABILITIESVIEW_H
