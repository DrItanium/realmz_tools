//
// Created by jwscoggins on 10/31/20.
//

#ifndef REALMZ_TOOLS_TACTICALSMODEL_H
#define REALMZ_TOOLS_TACTICALSMODEL_H
#include <QAbstractTableModel>
#include "RepresentationModel.h"
class TacticalsModel : public RepresentationModel {
public:
    explicit TacticalsModel(QObject* parent = nullptr) : RepresentationModel(parent) { }
    ~TacticalsModel() override = default;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    static constexpr int computeTacticalIndex(int row, int column) noexcept {
        return ((row * 6) + column) + 9000;
    }
    int computeProperIndex(int row, int column) const noexcept override {
        return computeTacticalIndex(row, column);
    }
    static constexpr int computeTacticalIndex(int portraitIndex) noexcept {
        return portraitIndex + 0x2227;
    }
    QString generateTacticalPath(int row, int column) const noexcept;
    QString generateProperPath(int row, int column) const noexcept override { return generateTacticalPath(row, column); }
};

#endif //REALMZ_TOOLS_TACTICALSMODEL_H
