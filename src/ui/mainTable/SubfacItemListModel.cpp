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

SubfacItemListModel::SubfacItemListModel(std::vector<std::shared_ptr<plan::LineTarget>> list, QObject *parent) :
	QAbstractTableModel(parent),
	item_list_(std::move(list)) {

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
    const auto& item = item_list_.at(index.row());
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

void SubfacItemListModel::refreshModel(std::vector<std::shared_ptr<plan::LineTarget>> new_list) {
    item_list_.clear();
	item_list_ = std::move(new_list);
    refreshModel();
}

std::shared_ptr<plan::LineTarget> SubfacItemListModel::getTarget(const QModelIndex& index) const {
    return item_list_.at(index.row());
}

}