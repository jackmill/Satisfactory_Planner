/**
 * @project Satisfactory_Planner
 * @file ProductionTableModel.h
 * 
 * @author Jackson Miller
 * @date 2021-11-01
 * @copyright (c) 2021 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_PRODUCTIONTABLEMODEL_H
#define SATISFACTORY_PLANNER_PRODUCTIONTABLEMODEL_H

#include <QAbstractTableModel>

#include "plan/Subfactory.h"
#include "data/Library.h"

namespace ui {

class ProductionTableModel : public QAbstractTableModel {
    Q_OBJECT
  public:
    explicit ProductionTableModel(plan::Subfactory& subfactory, std::shared_ptr<data::Library> db, QObject* parent = nullptr);

    [[nodiscard]] int rowCount(const QModelIndex &parent) const final;
    [[nodiscard]] int columnCount(const QModelIndex &parent) const final { return static_cast<int> (Column::Ingredients) + 1; };
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const final;
    [[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation, int role) const final;

    bool insertRows(int startRow, int count, const QModelIndex &parent, const data::Item &target);
    [[nodiscard]] data::Item getRowTarget(const QModelIndex &index) const;

    enum class Column {
        Checked = 0,
        Product,
        Recipe,
        Building,
        Power,
        Byproduct,
        Ingredients
    };

  private:
    plan::Subfactory& subfactory_;
    std::shared_ptr<data::Library> db_;

};

}

#endif //SATISFACTORY_PLANNER_PRODUCTIONTABLEMODEL_H
