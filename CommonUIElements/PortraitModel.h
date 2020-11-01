//
// Created by jwscoggins on 10/31/20.
//

#ifndef REALMZ_TOOLS_PORTRAITMODEL_H
#define REALMZ_TOOLS_PORTRAITMODEL_H

#include <QAbstractTableModel>
class PortraitModel : public QAbstractTableModel {
public:
    PortraitModel(QObject* parent = nullptr);
    ~PortraitModel() override = default;
    int columnCount(const QModelIndex& idx) const override;
    int rowCount(const QModelIndex& idx) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

};

#endif //REALMZ_TOOLS_PORTRAITMODEL_H
