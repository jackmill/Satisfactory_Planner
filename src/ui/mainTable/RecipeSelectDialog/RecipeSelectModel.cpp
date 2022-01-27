/**
 * @project Satisfactory_Planner
 * @file RecipeSelectModel.cpp
 * 
 * @author Jackson Miller
 * @date 2021-11-03
 * @copyright (c) 2021 Jackson Miller
 */

#include "RecipeSelectModel.h"
#include "../../util.h"

namespace ui {

RecipeSelectModel::RecipeSelectModel(std::vector<data::Recipe> recipes, QObject *parent) :
    recipes_(std::move(recipes)),
    QAbstractTableModel(parent) {
}

data::Recipe RecipeSelectModel::getSelectedRecipe(const QModelIndex &index) const {
    return recipes_.at(index.row());
}

int RecipeSelectModel::rowCount(const QModelIndex &parent) const {
    return static_cast<int>(recipes_.size());
}

int RecipeSelectModel::columnCount(const QModelIndex &parent) const {
    return column_count_;
}

QVariant RecipeSelectModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::ItemDataRole::DisplayRole || orientation != Qt::Horizontal) {
        return {};
    }

    const auto column = static_cast<Column> (section);
    switch(column) {
        case Column::kName :        return tr("Recipe");
        case Column::kIngredients : return tr("Ingredients");
		case Column::kArrow1 :      return {};
        case Column::kTime :        return tr("Time");
        case Column::kBuilding :    return tr("Building");
		case Column::kArrow2 :      return {};
        case Column::kProducts :    return tr("Products");
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

        } else if (column == Column::kTime) {
            return QString("%1 Sec").arg(recipe.time());

        } else if (column == Column::kBuilding) {
            return QString::fromStdString(recipe.machine().name());

        } else if (column == Column::kArrow1 || column == Column::kArrow2) {
			return QString(">");
		}

    } else if (role == Qt::ItemDataRole::DecorationRole) {
        if (column == Column::kBuilding) {
			return util::itemIconFromDisplayName(QString::fromStdString(recipe.machine().name()));
        }
    } else if (role == Qt::ItemDataRole::ToolTipRole) {
		if (column == Column::kIngredients) {
			QString ingredients_tooltip;
			const std::vector<data::Item>& ingredients = recipe.ingredientList();

			for (auto ingredient = ingredients.cbegin();
			     ingredient != ingredients.cend();
			     ++ingredient) {
				ingredients_tooltip += QString("%1 : %2").arg(QString::fromStdString(ingredient->name()),
				                                              QString::number(ingredient->amount()));

				if (ingredient != std::prev(ingredients.end())) {
					ingredients_tooltip += "\n";
				}
			}

			return ingredients_tooltip;

		} else if (column == Column::kProducts) {
			QString products_tooltip;
			const std::vector<data::Item>& products = recipe.productList();

			for (auto ingredient = products.cbegin();
			     ingredient != products.cend();
			     ++ingredient) {
				products_tooltip += QString("%1 : %2").arg(QString::fromStdString(ingredient->name()),
				                                           QString::number(ingredient->amount()));

				if (ingredient != std::prev(products.end())) {
					products_tooltip += "\n";
				}
			}

			return products_tooltip;

		} else if (column == Column::kBuilding) {
			return QString::fromStdString(recipe.machine().name());
		}

	} else if (role == Qt::ItemDataRole::TextAlignmentRole) {
		if (column == Column::kArrow1 || column == Column::kArrow2) {
			return Qt::AlignCenter;
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