/**
 * @project Satisfactory_Planner
 * @file SubfacItemListModel.h
 * 
 * @author Jackson Miller
 * @date 2021-11-07
 * @copyright (c) 2021 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_SUBFACITEMLISTMODEL_H
#define SATISFACTORY_PLANNER_SUBFACITEMLISTMODEL_H

#include <QAbstractTableModel>
#include <vector>
#include "plan/Subfactory.h"

namespace ui {

class SubfacItemListModel : public QAbstractTableModel {
    Q_OBJECT
  public:
    explicit SubfacItemListModel(std::vector<std::shared_ptr<data::Item>> list, QObject* parent = nullptr);

    [[nodiscard]] int columnCount(const QModelIndex& parent) const final { return static_cast<int> (Column::kRate) + 1; };
    [[nodiscard]] int rowCount(const QModelIndex& parent) const final { return static_cast<int> (item_list.size()); }

    [[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation, int role) const final;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;

    void refreshModel();
    void refreshModel(std::vector<std::shared_ptr<data::Item>> new_list);
    [[nodiscard]] std::shared_ptr<data::Item> getTarget(const QModelIndex& index) const;

    enum class Column {
        kItem = 0,
        kRate
    };

  private:
    std::vector<std::shared_ptr<data::Item>> item_list;
};

}

#endif //SATISFACTORY_PLANNER_SUBFACITEMLISTMODEL_H
