//
// Created by jwscoggins on 10/31/20.
//

#include "RepresentationModel.h"
#include <QImage>
#include <QPixmap>

QVariant
RepresentationModel::data(const QModelIndex &index, int role) const {
    auto path = generateProperPath(index.row(), index.column());
    QImage img(path);
    auto scale = generateScaleFactor();
    QPixmap pix;
    if (scale.width() != 0 && scale.height() != 0) {
        pix = QPixmap::fromImage(img.scaled(scale));
    } else {
        pix = QPixmap::fromImage(img);
    }
    if (role == Qt::DecorationRole) {
        return pix;
    } else if (role == Qt::SizeHintRole) {
        return pix.size();
    } else if (role == Qt::DisplayRole) {
        return "";
    } else {
        return QVariant();
    }
}