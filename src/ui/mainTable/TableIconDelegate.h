/**
 * @project Satisfactory_Planner
 * @file TableIconDelegate.h
 * 
 * @author Jackson Miller
 * @date 2022-01-01
 * @copyright (c) 2022 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_TABLEICONDELEGATE_H
#define SATISFACTORY_PLANNER_TABLEICONDELEGATE_H

#include <QStyledItemDelegate>

#include "plan/Subfactory.h"

namespace ui {

class TableIconDelegate final : public QStyledItemDelegate {
	Q_OBJECT
  public:
	explicit TableIconDelegate(std::shared_ptr<plan::Subfactory> subfactory, QWidget* parent);

	void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const final;
	[[nodiscard]] QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const final;

  private:
	std::shared_ptr<plan::Subfactory> subfactory_;

};

}

#endif //SATISFACTORY_PLANNER_TABLEICONDELEGATE_H