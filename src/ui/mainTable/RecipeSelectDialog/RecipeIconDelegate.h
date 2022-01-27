/**
 * @project Satisfactory_Planner
 * @file RecipeIconDelegate.h
 * 
 * @author Jackson Miller
 * @date 2022-01-10
 * @copyright (c) 2022 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_RECIPEICONDELEGATE_H
#define SATISFACTORY_PLANNER_RECIPEICONDELEGATE_H

#include <QStyledItemDelegate>

#include "data/Recipe.h"

namespace ui {

class RecipeIconDelegate : public QStyledItemDelegate {
	Q_OBJECT
  public:
	explicit RecipeIconDelegate(std::vector<data::Recipe> recipes, QWidget* parent = nullptr);

	void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
	[[nodiscard]] QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;

  private:
	std::vector<data::Recipe> recipes_;
};

} // namespace ui

#endif //SATISFACTORY_PLANNER_RECIPEICONDELEGATE_H
