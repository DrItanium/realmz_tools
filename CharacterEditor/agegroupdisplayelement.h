#ifndef AGEGROUPDISPLAYELEMENT_H
#define AGEGROUPDISPLAYELEMENT_H

#include <QWidget>
#include "../RaceData.h"
namespace Ui {
class AgeGroupDisplayElement;
}

class AgeGroupDisplayElement : public QWidget
{
    Q_OBJECT
public slots:
    void updateFields(realmz::AgeRange range, realmz::AgeModifiers mods);
private:
    void setAgeRange(const realmz::AgeRange& range);
    void setAgeModifier(const realmz::AgeModifiers& modifier);
public:
    explicit AgeGroupDisplayElement(QWidget *parent = nullptr);
    ~AgeGroupDisplayElement();

private:
    Ui::AgeGroupDisplayElement *ui;
};

#endif // AGEGROUPDISPLAYELEMENT_H
