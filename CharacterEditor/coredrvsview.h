#ifndef COREDRVSVIEW_H
#define COREDRVSVIEW_H

#include <QWidget>
#include "../DRVAdjustments.h"

namespace Ui {
class CoreDRVsView;
}

class CoreDRVsView : public QWidget
{
    Q_OBJECT

public:
    explicit CoreDRVsView(QWidget *parent = nullptr);
    ~CoreDRVsView();
public:

public slots:
    void populate(realmz::DRVAdjustments adj);

private:
    Ui::CoreDRVsView *ui;
};

#endif // COREDRVSVIEW_H
