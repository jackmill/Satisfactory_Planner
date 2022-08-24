/**
 * @project Satisfactory_Planner
 * @file ItemListModel.cpp
 *
 * @author Jackson Miller
 * @date 2021-10-05
 * @copyright (c) 2021 Jackson Miller
 */

#include <vector>
#include <QIcon>

#include "ItemListModel.h"
#include "../util.h"

namespace ui {

ItemListModel::ItemListModel(data::Library* db, QObject *parent) :
    db_(db),
    QAbstractListModel(parent) {
    assert(db_);
}

int ItemListModel::rowCount(const QModelIndex &parent) const {
    return static_cast<int>(db_->getItemsSorted().size());
}

int ItemListModel::columnCount(const QModelIndex &parent) const {
    return 1;
}

QVariant ItemListModel::data(const QModelIndex &index, int role) const {
    const data::Item &item = db_->getItemsSorted().at(index.row());

    if (role == Qt::ItemDataRole::DisplayRole) {
        return QString::fromStdString(item.name());
    } else if (role == Qt::ItemDataRole::DecorationRole) {
        return util::itemIconFromDisplayName(QString::fromStdString(item.name()));
    }

    return {};
}

data::Item ItemListModel::itemAtRow(int row_num) const {
    return db_->getItemsSorted().at(row_num);
}

}