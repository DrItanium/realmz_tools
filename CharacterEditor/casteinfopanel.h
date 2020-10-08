#ifndef CASTEINFOPANEL_H
#define CASTEINFOPANEL_H

#include <QWidget>

namespace Ui {
class CasteInfoPanel;
}

class CasteInfoPanel : public QWidget
{
    Q_OBJECT

public:
    explicit CasteInfoPanel(QWidget *parent = nullptr);
    ~CasteInfoPanel();

private:
    Ui::CasteInfoPanel *ui;
};

#endif // CASTEINFOPANEL_H
