//
// Created by jwscoggins on 10/31/20.
//

#include "TacticalsModel.h"

int TacticalsModel::rowCount(const QModelIndex &) const {
    return 20;
}

int TacticalsModel::columnCount(const QModelIndex &) const {
    return 6;
}

QVariant
TacticalsModel::data(const QModelIndex &index, int role) const {

}

TacticalsModel::TacticalsModel(QObject *parent) : QAbstractTableModel(parent) {

}