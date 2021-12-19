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

QVariant IngredientsModel::data(const QModelIndex &index, int role) const {
    const auto ingredient = subfactory_.ingredients_.at(index.row());
    const auto column = static_cast<Column> (index.column());

    if (role == Qt::ItemDataRole::DisplayRole) {
        if (column == Column::kItem) {
            return QString::fromStdString(ingredient.name());

        } else if (column == Column::kRate) {
            return QString::number(ingredient.rate());

        }

    } else if (role == Qt::ItemDataRole::DecorationRole) {
        if (column == Column::kItem) {
            return util::itemIconFromDisplayName(QString::fromStdString(ingredient.name()));

        }
    }

    return {};
}

}