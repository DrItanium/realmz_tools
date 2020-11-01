//
// Created by jwscoggins on 11/1/20.
//

#ifndef REALMZ_TOOLS_VIEWAGINGTABLEMODEL_H
#define REALMZ_TOOLS_VIEWAGINGTABLEMODEL_H
#include <QAbstractTableModel>
#include "../RaceData.h"
class ViewAgingTableModel : public QAbstractTableModel {
public:
    explicit ViewAgingTableModel(QObject* parent = nullptr) : QAbstractTableModel(parent) { }
    ~ViewAgingTableModel() override = default;
    int columnCount(const QModelIndex& idx) const override { return 5; }
    int rowCount(const QModelIndex& idx) const override { return 17; }
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    void setRaceKind(realmz::RaceKind k) noexcept;
private:
    realmz::RaceKind _rk = realmz::RaceKind::None;


};

#endif //REALMZ_TOOLS_VIEWAGINGTABLEMODEL_H
