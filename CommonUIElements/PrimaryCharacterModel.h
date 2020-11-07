//
// Created by jwscoggins on 11/6/20.
//

#ifndef REALMZ_TOOLS_PRIMARYCHARACTERMODEL_H
#define REALMZ_TOOLS_PRIMARYCHARACTERMODEL_H
#include <QAbstractTableModel>
#include "../Character.h"
#include <memory>
class PrimaryCharacterModel : public QAbstractTableModel  {
public:
    explicit PrimaryCharacterModel(std::shared_ptr<realmz::Character> ptr = nullptr, QObject* parent = nullptr) : QAbstractTableModel(parent), _cc(ptr) { }
    ~PrimaryCharacterModel() override = default;
    int columnCount(const QModelIndex& idx) const override { return 1; }
    int rowCount(const QModelIndex& idx) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    void setTargetCharacter(std::shared_ptr<realmz::Character> cc) noexcept {
        _cc = cc;
    }
    const auto& getTargetCharacter() const noexcept { return _cc; }
private:
    std::shared_ptr<realmz::Character> _cc;
};

#endif //REALMZ_TOOLS_PRIMARYCHARACTERMODEL_H
