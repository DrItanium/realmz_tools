//
// Created by jwscoggins on 10/31/20.
//

#include "PortraitModel.h"
#include "ApplicationUtilities.h"

QString
PortraitModel::generatePortraitPath(int row, int column) const noexcept {
    auto fsPath = getPortraitsDirectory() / (QString::number(computeProperIndex(row,column)) + tr(".png")).toStdString();
    return QString(fsPath.string().c_str());
}

