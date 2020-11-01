//
// Created by jwscoggins on 10/31/20.
//

#ifndef REALMZ_TOOLS_PORTRAITMODEL_H
#define REALMZ_TOOLS_PORTRAITMODEL_H

#include <QAbstractTableModel>
#include "RepresentationModel.h"
class PortraitModel : public RepresentationModel {
public:
    explicit PortraitModel(QObject* parent = nullptr) : RepresentationModel(parent) { }
    ~PortraitModel() override = default;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
public:
    static constexpr auto computePortraitIndex(int row, int column) noexcept -> int {
        return ((row * 6) + column) + 257;
    }
    int computeProperIndex(int row, int column) const noexcept override {
        return computePortraitIndex(row, column);
    }

    QString generatePortraitPath(int row, int column) const noexcept;
    QString generateProperPath(int row, int column) const noexcept override { return generatePortraitPath(row, column); }
};

#endif //REALMZ_TOOLS_PORTRAITMODEL_H
