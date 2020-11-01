//
// Created by jwscoggins on 11/1/20.
//

#include "ViewAgingTableModel.h"
#include "../AgeGroup.h"
#include <sstream>
QVariant
ViewAgingTableModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        if (_rk == realmz::RaceKind::None) {
            return "";
        }
        // okay so design is each column represents an age group (add one to the column to get the proper value)
        // each row is a given stat
        const auto& raceData = realmz::loadRaceData(_rk);
        auto targetAgeGroup = static_cast<realmz::AgeGroup>(index.column() + 1);
        const auto& ageMods = raceData.getAgeModifier(targetAgeGroup);
        const auto& ageRanges = raceData.getAgeRange(targetAgeGroup);
        auto mkStr = [](auto value) noexcept { return QString::number(static_cast<int>(value)); };
        switch (index.row()) {
            case 0: return mkStr(ageRanges.getFrom());
            case 1: return mkStr(ageRanges.getTo());
            case 2: return mkStr(ageMods.getBrawn());
            case 3: return mkStr(ageMods.getKnowledge());
            case 4: return mkStr(ageMods.getJudgment());
            case 5: return mkStr(ageMods.getAgility());
            case 6: return mkStr(ageMods.getVitality());
            case 7: return mkStr(ageMods.getLuck());
            case 8: return mkStr(ageMods.getMagicResist());
            case 9: return mkStr(ageMods.getMovement());
            case 10: return mkStr(ageMods.getCharm());
            case 11: return mkStr(ageMods.getHeat());
            case 12: return mkStr(ageMods.getCold());
            case 13: return mkStr(ageMods.getElectrical());
            case 14: return mkStr(ageMods.getChemical());
            case 15: return mkStr(ageMods.getMental());
            case 16: return mkStr(ageMods.getMagical());
            default: return "";
        }
    }
    return QVariant();
}

QVariant
ViewAgingTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    static const QString RowHeaders[] {
        tr("From Age"),
        tr("To Age"),
        tr("Brawn"),
        tr("Knowledge"),
        tr("Judgment"),
        tr("Agility"),
        tr("Vitality"),
        tr("Luck"),
        tr("Magic Resist"),
        tr("Movement"),
        tr("Charm"),
        tr("Heat"),
        tr("Cold"),
        tr("Electrical"),
        tr("Chemical"),
        tr("Mental"),
        tr("Magical")
    };
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Orientation::Vertical) {
           // row
           return RowHeaders[section];
        } else if (orientation == Qt::Orientation::Horizontal){
            // column
            std::stringstream bldr;
            auto targetGroup = static_cast<realmz::AgeGroup>(section+1);
            bldr << targetGroup;
            auto tmp = bldr.str();
            return QString(tmp.c_str());
        }
    }
    return QVariant();
}

void
ViewAgingTableModel::setRaceKind(realmz::RaceKind k) noexcept {
    _rk = k;
}