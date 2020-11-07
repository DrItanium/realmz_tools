//
// Created by jwscoggins on 11/6/20.
//

#ifndef REALMZ_TOOLS_DRVMODEL_H
#define REALMZ_TOOLS_DRVMODEL_H
#include <QAbstractTableModel>
#include "../Character.h"
class DRVModel /*: public QAbstractTableModel */ {
public:
#if 0
    explicit DRVModel(const realmz::Character& currentCharacter, QObject* parent = nullptr) : QAbstractTableModel(parent) { }
    ~DRVModel() override = default;
    int columnCount(const QModelIndex& idx) const override { return 2; }
    int rowCount(const QModelIndex& idx) const override { return 20; }
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    virtual int computeProperIndex(int row, int column) const noexcept = 0;
    virtual QString generateProperPath(int row, int column) const noexcept = 0;
    virtual QSize generateScaleFactor() const noexcept { return {128,128}; }
private:
    std::reference_wrapper<const realmz::Character> _currentCharacter;
#endif
};

#endif //REALMZ_TOOLS_DRVMODEL_H
