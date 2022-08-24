/**
 * @project Satisfactory_Planner
 * @file IngredientsModel.h
 * 
 * @author Jackson Miller
 * @date 2021-11-07
 * @copyright (c) 2021 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_INGREDIENTSMODEL_H
#define SATISFACTORY_PLANNER_INGREDIENTSMODEL_H

#include <QAbstractTableModel>
#include <vector>
#include "plan/Subfactory.h"

namespace ui {

class IngredientsModel : public QAbstractTableModel {
    Q_OBJECT
  public:
    explicit IngredientsModel(plan::Subfactory** subfactory, QObject* parent = nullptr);

    [[nodiscard]] int columnCount(const QModelIndex& parent) const final { return static_cast<int> (Column::kRate) + 1; };
    [[nodiscard]] int rowCount(const QModelIndex& parent) const final { return (*subfactory_)->numIngredients(); }

    [[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation, int role) const final;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;

    void refreshModel();

    enum class Column {
        kItem = 0,
        kRate
    };

  private:
	plan::Subfactory** subfactory_;
};

}

#endif //SATISFACTORY_PLANNER_INGREDIENTSMODEL_H
