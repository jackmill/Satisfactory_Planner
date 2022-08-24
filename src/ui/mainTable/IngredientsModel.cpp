/**
 * @project Satisfactory_Planner
 * @file IngredientsModel.cpp
 * 
 * @author Jackson Miller
 * @date 2021-11-07
 * @copyright (c) 2021 Jackson Miller
 */

#include "IngredientsModel.h"
#include "../util.h"

namespace ui {

IngredientsModel::IngredientsModel(plan::Subfactory** subfactory, QObject *parent) :
	QAbstractTableModel(parent),
	subfactory_(subfactory) {
	assert(subfactory_);
}

QVariant IngredientsModel::headerData(int section, Qt::Orientation orientation, int role) const {
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

QVariant IngredientsModel::data(const QModelIndex &index, int role) const {
    const auto& item = (*subfactory_)->ingredientAt(index.row());
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

void IngredientsModel::refreshModel() {
    beginResetModel();
    endResetModel();
}

}