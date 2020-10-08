#ifndef ICONSELECT6_H
#define ICONSELECT6_H

#include <QWidget>

namespace Ui {
class IconSelect6;
}

class IconSelect6 : public QWidget
{
    Q_OBJECT

public:
    explicit IconSelect6(QWidget *parent = nullptr);
    ~IconSelect6();

private:
    Ui::IconSelect6 *ui;
};

#endif // ICONSELECT6_H
