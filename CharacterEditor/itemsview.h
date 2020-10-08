#ifndef ITEMSVIEW_H
#define ITEMSVIEW_H

#include <QWidget>

namespace Ui {
class ItemsView;
}

class ItemsView : public QWidget
{
    Q_OBJECT

public:
    explicit ItemsView(QWidget *parent = nullptr);
    ~ItemsView();

private:
    Ui::ItemsView *ui;
};

#endif // ITEMSVIEW_H
