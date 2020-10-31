#ifndef SIXPICTUREWIDGET_H
#define SIXPICTUREWIDGET_H

#include <QWidget>
#include <QString>

namespace Ui {
class SixPictureWidget;
}

class SixPictureWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SixPictureWidget(QWidget *parent = nullptr);
    ~SixPictureWidget();
public slots:
    void setIcons(QString, QString, QString, QString, QString, QString);
private slots:
    void icon6Selected();
    void icon5Selected();
    void icon4Selected();
    void icon3Selected();
    void icon2Selected();
    void icon1Selected();
signals:
    void iconSelected(int index);
private:
    Ui::SixPictureWidget *ui;
};

#endif // SIXPICTUREWIDGET_H
