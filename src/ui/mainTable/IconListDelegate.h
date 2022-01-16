/**
 * @project Satisfactory_Planner
 * @file IconListDelegate.h
 * 
 * @author Jackson Miller
 * @date 2022-01-10
 * @copyright (c) 2022 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_ICONLISTDELEGATE_H
#define SATISFACTORY_PLANNER_ICONLISTDELEGATE_H

#include <QStyledItemDelegate>

#include "plan/Subfactory.h"

namespace ui {

class IconListDelegate final : public QStyledItemDelegate {
	Q_OBJECT
  public:
	explicit IconListDelegate(plan::Subfactory_Ptr subfactory, QWidget* parent);

	void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const final;
	[[nodiscard]] QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const final;

  private:
	plan::Subfactory_Ptr subfactory_;
};

} // namespace ui

#endif //SATISFACTORY_PLANNER_ICONLISTDELEGATE_H
