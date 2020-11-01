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
public:
    static constexpr auto computePortraitIndex(int row, int column) noexcept -> int {
        return ((row * 6) + column) + 257;
    }
    QString generatePortraitPath(int row, int column) const noexcept;
};

#endif //REALMZ_TOOLS_PORTRAITMODEL_H