/**
 * @project Satisfactory_Planner
 * @file RecipeSelectModel.cpp
 * 
 * @author Jackson Miller
 * @date 2021-11-03
 * @copyright (c) 2021 Jackson Miller
 */

#include "RecipeSelectModel.h"

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
    return static_cast<int> (Column::kProducts) + 1;
}

QVariant RecipeSelectModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::ItemDataRole::DisplayRole || orientation != Qt::Horizontal) {
        return {};
    }

    const auto column = static_cast<Column> (section);
    switch(column) {
        case Column::kName :        return tr("Recipe");
        case Column::kIngredients : return tr("Ingredients");
        case Column::kBuilding :    return tr("Building");
        case Column::kProducts :    return tr("Products");
    }

    return {};
}

QVariant RecipeSelectModel::data(const QModelIndex &index, int role) const {
    const auto recipe = recipes_.at(index.row());
    const auto column = static_cast<Column> (index.column());

    if (role == Qt::ItemDataRole::DisplayRole) {
        if (column == Column::kName) {
            return QString::fromStdString(recipe.name());

        } else if (column == Column::kIngredients) {
            QString ingredient_string;
            std::vector<data::Item> ingredients = recipe.ingredientList();
            for (auto ingredient = ingredients.cbegin(); ingredient != ingredients.cend(); ++ingredient) {
                ingredient_string += QString::fromStdString(ingredient->name());
                ingredient_string += " : ";
                ingredient_string += QString::number(ingredient->amount());

                if (ingredient + 1 != ingredients.cend()) {
                    ingredient_string += ", ";
                }
            }
            return ingredient_string;

        } else if (column == Column::kBuilding) {
            return QString::fromStdString(recipe.machine().name());

        } else if (column == Column::kProducts) {
            QString product_string;
            std::vector<data::Item> products = recipe.productList();
            for (auto product = products.cbegin(); product != products.cend(); ++product) {
                product_string += QString::fromStdString(product->name());
                product_string += " : ";
                product_string += QString::number(product->amount());

                if (product + 1 != products.cend()) {
                    product_string += ", ";
                }
            }
            return product_string;

        }
    }

    return {};
}

}