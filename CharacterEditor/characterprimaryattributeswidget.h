#ifndef CHARACTERPRIMARYATTRIBUTESWIDGET_H
#define CHARACTERPRIMARYATTRIBUTESWIDGET_H

#include <QWidget>
#include "../Attribute.h"
#include "../Attributes.h"

namespace Ui {
class CharacterPrimaryAttributesWidget;
}

class CharacterPrimaryAttributesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CharacterPrimaryAttributesWidget(QWidget *parent = nullptr);
    ~CharacterPrimaryAttributesWidget();
public slots:
    void updateFields(realmz::Attributes attribs);

private:
    Ui::CharacterPrimaryAttributesWidget *ui;
};

#endif // CHARACTERPRIMARYATTRIBUTESWIDGET_H
