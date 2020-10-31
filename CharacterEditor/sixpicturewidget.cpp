#include "sixpicturewidget.h"
#include "ui_sixpicturewidget.h"

SixPictureWidget::SixPictureWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SixPictureWidget)
{
    ui->setupUi(this);
}

SixPictureWidget::~SixPictureWidget()
{
    delete ui;
}

void
SixPictureWidget::icon1Selected() {

}

void
SixPictureWidget::icon2Selected() {

}

void
SixPictureWidget::icon3Selected() {

}

void
SixPictureWidget::icon4Selected() {

}

void
SixPictureWidget::icon5Selected() {

}

void
SixPictureWidget::icon6Selected() {

}

void
SixPictureWidget::setIcons(QString i1, QString i2, QString i3, QString i4, QString i5, QString i6) {
}
