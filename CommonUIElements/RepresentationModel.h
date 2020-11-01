//
// Created by jwscoggins on 10/31/20.
//

#ifndef REALMZ_TOOLS_REPRESENTATIONMODEL_H
#define REALMZ_TOOLS_REPRESENTATIONMODEL_H
#include <QAbstractTableModel>
#include <QSize>
class RepresentationModel : public QAbstractTableModel {
public:
    explicit RepresentationModel(QObject* parent = nullptr) : QAbstractTableModel(parent) { }
    ~RepresentationModel() override = default;
    int columnCount(const QModelIndex& idx) const override { return 6; }
    int rowCount(const QModelIndex& idx) const override { return 20; }
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    virtual int computeProperIndex(int row, int column) const noexcept = 0;
    virtual QString generateProperPath(int row, int column) const noexcept = 0;
    virtual QSize generateScaleFactor() const noexcept { return {128,128}; }
};

#endif //REALMZ_TOOLS_REPRESENTATIONMODEL_H
