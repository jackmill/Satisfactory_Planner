/**
 * @project Satisfactory_Planner
 * @file ByproductModel.h
 * 
 * @author Jackson Miller
 * @date 2021-11-07
 * @copyright (c) 2021 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_BYPRODUCTMODEL_H
#define SATISFACTORY_PLANNER_BYPRODUCTMODEL_H

#include "ItemViewModel.h"
#include "plan/Subfactory.h"

namespace ui {

class ByproductModel : public ItemViewModel {
    Q_OBJECT
  public:
    explicit ByproductModel(plan::Subfactory& subfactory, QObject* parent = nullptr) : ItemViewModel(subfactory, parent) {};

    [[nodiscard]] QVariant data(const QModelIndex& index, int role) const final;

};

}

#endif //SATISFACTORY_PLANNER_BYPRODUCTMODEL_H
