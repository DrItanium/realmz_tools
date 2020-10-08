#ifndef CONDITIONSVIEW_H
#define CONDITIONSVIEW_H

#include <QWidget>

namespace Ui {
class ConditionsView;
}

class ConditionsView : public QWidget
{
    Q_OBJECT

public:
    explicit ConditionsView(QWidget *parent = nullptr);
    ~ConditionsView();

private:
    Ui::ConditionsView *ui;
};

#endif // CONDITIONSVIEW_H
