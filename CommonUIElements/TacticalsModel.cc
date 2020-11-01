//
// Created by jwscoggins on 10/31/20.
//

#include "TacticalsModel.h"
#include "ApplicationUtilities.h"
#include <QMessageBox>

QString
TacticalsModel::generateTacticalPath(int row, int column) const noexcept {
    auto fsPath = getTacticalsDirectory() / (QString::number(computeProperIndex(row,column)) + tr(".png")).toStdString();
    return QString(fsPath.string().c_str());
}
