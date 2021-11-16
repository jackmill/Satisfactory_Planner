/**
 * @project Satisfactory_Planner
 * @file TargetModel.h
 * 
 * @author Jackson Miller
 * @date 2021-11-05
 * @copyright (c) 2021 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_TARGETMODEL_H
#define SATISFACTORY_PLANNER_TARGETMODEL_H

#include <QAbstractTableModel>

#include "ItemViewModel.h"
#include "data/Library.h"
#include "plan/Subfactory.h"

namespace ui {

class TargetModel : public ItemViewModel {
    Q_OBJECT
  public:
    explicit TargetModel(std::shared_ptr<data::Library> db, plan::Subfactory& subfactory, QObject* parent = nullptr);

    [[nodiscard]] int rowCount(const QModelIndex& parent) const final { return subfactory_.product_targets_.size(); };
    [[nodiscard]] QVariant data(const QModelIndex& index, int role) const final;

    bool insertRows(int startRow, int count, const QModelIndex &parent) final;
    bool removeRows(int startRow, int count, const QModelIndex &parent) final;
    void editRow(const QModelIndex &index);

    [[nodiscard]] data::Item getTarget(const QModelIndex &index) const;

  private:
    std::shared_ptr<data::Library> db_;

};

}

#endif //SATISFACTORY_PLANNER_TARGETMODEL_H
