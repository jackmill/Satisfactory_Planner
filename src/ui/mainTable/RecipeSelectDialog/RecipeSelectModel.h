/**
 * @project Satisfactory_Planner
 * @file RecipeSelectModel.h
 * 
 * @author Jackson Miller
 * @date 2021-11-03
 * @copyright (c) 2021 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_RECIPESELECTMODEL_H
#define SATISFACTORY_PLANNER_RECIPESELECTMODEL_H

#include <QAbstractTableModel>

#include "data/Library.h"

namespace ui {

class RecipeSelectModel : public QAbstractTableModel {
    Q_OBJECT
  public:
    explicit RecipeSelectModel(std::vector<data::Recipe> recipes, QObject* parent = nullptr);

    [[nodiscard]] data::Recipe getSelectedRecipe(const QModelIndex &index) const;

    [[nodiscard]] int rowCount(const QModelIndex &parent) const final;
    [[nodiscard]] int columnCount(const QModelIndex &parent) const final;
    [[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation, int role) const final;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const final;

	enum class Column {
		kName = 0,
		kIngredients,
		kArrow1,
		kTime,
		kBuilding,
		kArrow2,
		kProducts
	};

	const static int column_count_ = static_cast<int>(Column::kProducts) + 1;

  private:
    std::vector<data::Recipe> recipes_;

    [[nodiscard]] static QVariant ingredientData(int col_index, const data::Recipe &recipe);
    [[nodiscard]] static QIcon ingredientIcon(int col_index, const data::Recipe& recipe);

};

}

#endif //SATISFACTORY_PLANNER_RECIPESELECTMODEL_H
