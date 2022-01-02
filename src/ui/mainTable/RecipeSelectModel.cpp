/**
 * @project Satisfactory_Planner
 * @file RecipeSelectModel.cpp
 * 
 * @author Jackson Miller
 * @date 2021-11-03
 * @copyright (c) 2021 Jackson Miller
 */

#include "RecipeSelectModel.h"
#include "../util.h"

namespace ui {

RecipeSelectModel::RecipeSelectModel(std::vector<data::Recipe> recipes, QObject *parent) :
    recipes_(std::move(recipes)),
    QAbstractTableModel(parent) {
}

data::Recipe RecipeSelectModel::getSelectedRecipe(const QModelIndex &index) const {
    return recipes_.at(index.row());
}

int RecipeSelectModel::rowCount(const QModelIndex &parent) const {
    return recipes_.size();
}

int RecipeSelectModel::columnCount(const QModelIndex &parent) const {
    return static_cast<int> (Column::kProduct2) + 1;
}

QVariant RecipeSelectModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::ItemDataRole::DisplayRole || orientation != Qt::Horizontal) {
        return {};
    }

    const auto column = static_cast<Column> (section);
    switch(column) {
        case Column::kName :        return tr("Recipe");
        case Column::kIngredient1 : return tr("Ingredient 1");
        case Column::kIngredient2 : return tr("Ingredient 2");
        case Column::kIngredient3 : return tr("Ingredient 3");
        case Column::kIngredient4 : return tr("Ingredient 4");
        case Column::kTime :        return tr("Time");
        case Column::kBuilding :    return tr("Building");
        case Column::kProduct1 :    return tr("Product 1");
        case Column::kProduct2 :    return tr("Product 2");
    }

    return {};
}

QVariant RecipeSelectModel::data(const QModelIndex &index, int role) const {
    const auto& recipe = recipes_.at(index.row());
    const auto& product_list = recipe.productList();
    const auto column = static_cast<Column> (index.column());

    if (role == Qt::ItemDataRole::DisplayRole) {
        if (column == Column::kName) {
            return QString::fromStdString(recipe.name());

        } else if (column == Column::kIngredient1) { return ingredientData(0, recipe);
        } else if (column == Column::kIngredient2) { return ingredientData(1, recipe);
        } else if (column == Column::kIngredient3) { return ingredientData(2, recipe);
        } else if (column == Column::kIngredient4) {
            return ingredientData(3, recipe);

        } else if (column == Column::kTime) {
            return QString("%1 Sec").arg(recipe.time());

        } else if (column == Column::kBuilding) {
            return QString::fromStdString(recipe.machine().name());

        } else if (column == Column::kProduct1) {
            return QString("%1 : %2").arg(QString::fromStdString(recipe.productList().at(0).name())).arg(recipe.productList().at(0).amount());
        } else if (column == Column::kProduct2) {
            if (product_list.size() > 1) {
                return QString("%1 : %2").arg(QString::fromStdString(recipe.productList().at(1).name())).arg(recipe.productList().at(1).amount());
            }
        }
    } else if (role == Qt::ItemDataRole::DecorationRole) {
        if (column == Column::kIngredient1) { return ingredientIcon(0, recipe);
        } else if (column == Column::kIngredient2) { return ingredientIcon(1, recipe);
        } else if (column == Column::kIngredient3) { return ingredientIcon(2, recipe);
        } else if (column == Column::kIngredient4) { return ingredientIcon(3, recipe);
        } else if (column == Column::kBuilding) { return util::itemIconFromDisplayName(QString::fromStdString(recipe.machine().name()));
        } else if (column == Column::kProduct1) { return util::itemIconFromDisplayName(QString::fromStdString(recipe.productList().at(0).name()));
        } else if (column == Column::kProduct2) {
            if (product_list.size() > 1 ) {
                return util::itemIconFromDisplayName(QString::fromStdString(recipe.productList().at(1).name()));
            }
        }
    }

    return {};
}

QVariant RecipeSelectModel::ingredientData(int col_index, const data::Recipe &recipe) {
    std::vector<data::Item> ingredient_list = recipe.ingredientList();

    if (ingredient_list.size() > col_index) {
        return QString("%1 : %2").arg(QString::fromStdString(ingredient_list.at(col_index).name())).arg(ingredient_list.at(col_index).amount());
    } else {
        return {};
    }
}

QIcon RecipeSelectModel::ingredientIcon(int col_index, const data::Recipe &recipe) {
    std::vector<data::Item> ingredient_list = recipe.ingredientList();

    if (ingredient_list.size() > col_index) {
        return util::itemIconFromDisplayName(QString::fromStdString(ingredient_list.at(col_index).name()));
    } else {
        return {};
    }
}


}