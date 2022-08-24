/**
 * @project Satisfactory_Planner
 * @file SubfactoryListModel.h
 * 
 * @author Jackson Miller
 * @date 2021-10-06
 * @copyright (c) 2021 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_SUBFACTORYLISTMODEL_H
#define SATISFACTORY_PLANNER_SUBFACTORYLISTMODEL_H

#include <QAbstractListModel>

#include "plan/Factory.h"

namespace ui {

class SubfactoryListModel : public QAbstractListModel {
    Q_OBJECT
  public:
    explicit SubfactoryListModel(plan::Factory* factory, QObject* parent= nullptr);

    bool updateSubfactory(int row, const plan::Subfactory &subfactory);

    [[nodiscard]] int rowCount(const QModelIndex &parent) const final;
    [[nodiscard]] int columnCount(const QModelIndex &parent) const final { return 1; };
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const final;

    bool insertRow(int startRow, const QModelIndex& parent, const plan::Subfactory& subfactory);
    bool removeRows(int startRow, int count, const QModelIndex &parent) final;

  private:
    plan::Factory* factory_;


};

}

#endif //SATISFACTORY_PLANNER_SUBFACTORYLISTMODEL_H
