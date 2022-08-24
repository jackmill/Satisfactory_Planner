/**
 * @project Satisfactory_Planner
 * @file ItemListModel.h
 *
 * @author Jackson Miller
 * @date 2021-10-05
 * @copyright (c) 2021 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_ITEMLISTMODEL_H
#define SATISFACTORY_PLANNER_ITEMLISTMODEL_H

#include <QAbstractListModel>

#include "data/Library.h"

namespace ui {

class ItemListModel : public QAbstractListModel {
    Q_OBJECT
  public:
    explicit ItemListModel(data::Library* db, QObject* parent = nullptr);

    [[nodiscard]] int rowCount(const QModelIndex &parent) const final;
    [[nodiscard]] int columnCount(const QModelIndex &parent) const final;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const final;

    [[nodiscard]] data::Item itemAtRow(int row_num) const;

  private:
    data::Library* db_;

};

}

#endif //SATISFACTORY_PLANNER_ITEMLISTMODEL_H
