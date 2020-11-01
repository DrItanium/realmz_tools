//
// Created by jwscoggins on 10/31/20.
//

#include "PortraitModel.h"

QVariant
PortraitModel::data(const QModelIndex &index, int role) const {

}

int PortraitModel::columnCount(const QModelIndex &idx) const {
    return 6;
}

int PortraitModel::rowCount(const QModelIndex &idx) const {
    return 20;
}

PortraitModel::PortraitModel(QObject *parent) : QAbstractTableModel(parent)
{

}
