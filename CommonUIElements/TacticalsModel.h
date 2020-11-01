//
// Created by jwscoggins on 10/31/20.
//

#ifndef REALMZ_TOOLS_TACTICALSMODEL_H
#define REALMZ_TOOLS_TACTICALSMODEL_H
#include <QAbstractTableModel>
class TacticalsModel : public QAbstractTableModel {
public:
    TacticalsModel(QObject* parent = nullptr);
    ~TacticalsModel() override = default;
    int columnCount(const QModelIndex& idx) const override;
    int rowCount(const QModelIndex& idx) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

};

#endif //REALMZ_TOOLS_TACTICALSMODEL_H
