#ifndef SPECIALINFOVIEW_H
#define SPECIALINFOVIEW_H

#include <QWidget>

namespace Ui {
class SpecialInfoView;
}

class SpecialInfoView : public QWidget
{
    Q_OBJECT

public:
    explicit SpecialInfoView(QWidget *parent = nullptr);
    ~SpecialInfoView();

private:
    Ui::SpecialInfoView *ui;
};

#endif // SPECIALINFOVIEW_H
