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

  private:
    std::vector<data::Recipe> recipes_;

    enum class Column {
        kName = 0,
        kIngredients,
        kBuilding,
        kProducts
    };

};

}

#endif //SATISFACTORY_PLANNER_RECIPESELECTMODEL_H
