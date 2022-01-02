/**
 * @project Satisfactory_Planner
 * @file ItemIconDelegate.h
 * 
 * @author Jackson Miller
 * @date 2022-01-01
 * @copyright (c) 2022 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_ITEMICONDELEGATE_H
#define SATISFACTORY_PLANNER_ITEMICONDELEGATE_H

#include <QStyledItemDelegate>

#include "plan/Subfactory.h"

namespace ui {

class ItemIconDelegate final : public QStyledItemDelegate {
	Q_OBJECT
  public:
	explicit ItemIconDelegate(std::shared_ptr<plan::Subfactory> subfactory, QObject* parent = nullptr);

	void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
	QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;

  private:
	std::shared_ptr<plan::Subfactory> subfactory_;


};

}

#endif //SATISFACTORY_PLANNER_ITEMICONDELEGATE_H
