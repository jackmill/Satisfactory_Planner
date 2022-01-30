/**
 * @project Satisfactory_Planner
 * @file ProductModel.h
 * 
 * @author Jackson Miller
 * @date 2021-11-05
 * @copyright (c) 2021 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_PRODUCTMODEL_H
#define SATISFACTORY_PLANNER_PRODUCTMODEL_H

#include <QAbstractTableModel>

#include "data/Library.h"
#include "plan/Subfactory.h"

namespace ui {

class ProductModel final : public QAbstractTableModel {
    Q_OBJECT
  public:
    explicit ProductModel(std::shared_ptr<data::Library> db, plan::Subfactory_Ptr subfactory, QObject* parent = nullptr);

    [[nodiscard]] int rowCount(const QModelIndex& parent) const final { return static_cast<int>((*subfactory_)->products_.size()); };
    [[nodiscard]] int columnCount(const QModelIndex &parent) const final { return static_cast<int> (Column::kRate) + 1; };
    [[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    [[nodiscard]] QVariant data(const QModelIndex& index, int role) const final;
	bool setData(const QModelIndex& index, const QVariant& value, int role) final;
	[[nodiscard]] Qt::ItemFlags flags(const QModelIndex& index) const final;

	bool insertRows(int startRow, const QModelIndex &parent, const std::shared_ptr<plan::LineTarget>& new_target);
    bool removeRows(int startRow, int count, const QModelIndex &parent) final;

    [[nodiscard]] std::shared_ptr<plan::LineTarget> getTarget(const QModelIndex &index) const;
	void refreshModel();

    enum class Column {
        kItem = 0,
        kRate
    };

  private:
    std::shared_ptr<data::Library> db_;
    plan::Subfactory_Ptr subfactory_;

};

}

#endif //SATISFACTORY_PLANNER_PRODUCTMODEL_H
