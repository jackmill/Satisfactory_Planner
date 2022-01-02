/**
 * @project Satisfactory_Planner
 * @file SubfacItemListModel.cpp
 * 
 * @author Jackson Miller
 * @date 2021-11-07
 * @copyright (c) 2021 Jackson Miller
 */

#include "SubfacItemListModel.h"
#include "../util.h"

namespace ui {

SubfacItemListModel::SubfacItemListModel(std::vector<std::shared_ptr<data::Item>> list, QObject *parent) :
    item_list(std::move(list)),
    QAbstractTableModel(parent) {

}

QVariant SubfacItemListModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::ItemDataRole::DisplayRole || orientation != Qt::Horizontal) {
        return {};
    }

    const auto column = static_cast<Column> (section);
    switch (column) {
        case Column::kItem :      return tr("Item");
        case Column::kRate :      return tr("Rate");
    }

    return {};
}

QVariant SubfacItemListModel::data(const QModelIndex &index, int role) const {
    const auto& item = item_list.at(index.row());
    const auto column = static_cast<Column> (index.column());

    if (role == Qt::ItemDataRole::DisplayRole) {
        if (column == Column::kItem) {
            return QString::fromStdString(item->name());
        } else if (column == Column::kRate) {
            return item->rate();
        }
    } else if (role == Qt::ItemDataRole::DecorationRole) {
        if (column == Column::kItem) {
            return util::itemIconFromDisplayName(QString::fromStdString(item->name()));
        }
    }

    return {};
}

void SubfacItemListModel::refreshModel() {
    beginResetModel();
    endResetModel();
}

void SubfacItemListModel::refreshModel(std::vector<std::shared_ptr<data::Item>> new_list) {
    item_list.clear();
    item_list = std::move(new_list);
    refreshModel();
}

std::shared_ptr<data::Item> SubfacItemListModel::getTarget(const QModelIndex& index) const {
    return item_list.at(index.row());
}

}