/**
 * @project Satisfactory_Planner
 * @file ItemViewModel.h
 * 
 * @author Jackson Miller
 * @date 2021-11-07
 * @copyright (c) 2021 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_ITEMVIEWMODEL_H
#define SATISFACTORY_PLANNER_ITEMVIEWMODEL_H

#include <QAbstractTableModel>
#include "plan/Subfactory.h"

namespace ui {

class ItemViewModel : public QAbstractTableModel {
    Q_OBJECT
  public:
    explicit ItemViewModel(plan::Subfactory& subfactory, QObject* parent = nullptr);

    [[nodiscard]] int columnCount(const QModelIndex& parent) const final { return static_cast<int> (Column::kRate) + 1; };
    [[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation, int role) const final;

  protected:
    plan::Subfactory& subfactory_;

    enum class Column {
        kItem = 0,
        kRate
    };
};

}

#endif //SATISFACTORY_PLANNER_ITEMVIEWMODEL_H
