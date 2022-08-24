//
// Created by Jackson Miller on 8/22/22.
//

#ifndef SATISFACTORY_PLANNER_BYPRODUCTSMODEL_H
#define SATISFACTORY_PLANNER_BYPRODUCTSMODEL_H

#include <QAbstractTableModel>
#include <vector>
#include "plan/Subfactory.h"

namespace ui {

class ByproductsModel : public QAbstractTableModel {
  Q_OBJECT
  public:
	explicit ByproductsModel(plan::Subfactory** subfactory, QObject* parent = nullptr);

	[[nodiscard]] int columnCount(const QModelIndex& parent) const final { return static_cast<int> (Column::kRate) + 1; };
	[[nodiscard]] int rowCount(const QModelIndex& parent) const final { return (*subfactory_)->numByproducts(); }

	[[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation, int role) const final;
	[[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;

	void refreshModel();
	void refreshModel(std::vector<std::shared_ptr<plan::TableItem>> new_list);
	[[nodiscard]] std::shared_ptr<plan::TableItem> getTarget(const QModelIndex& index) const;

	enum class Column {
		kItem = 0,
		kRate
	};

  private:
	plan::Subfactory** subfactory_;
};

}

#endif //SATISFACTORY_PLANNER_BYPRODUCTSMODEL_H
