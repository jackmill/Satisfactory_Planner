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

#include "ItemViewModel.h"

namespace ui {

class IngredientsModel : public ItemViewModel {
    Q_OBJECT
  public:
    explicit IngredientsModel(plan::Subfactory& subfactory, QObject* parent = nullptr) : ItemViewModel(subfactory, parent) {};

    [[nodiscard]] int rowCount(const QModelIndex &parent) const final { return subfactory_.ingredients_.size(); };
    [[nodiscard]] QVariant data(const QModelIndex& index, int role) const final;

};

}

#endif //SATISFACTORY_PLANNER_INGREDIENTSMODEL_H
