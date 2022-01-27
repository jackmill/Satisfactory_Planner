/**
 * @project Satisfactory_Planner
 * @file SpinBoxDelegate.h
 * 
 * @author Jackson Miller
 * @date 2022-01-01
 * @copyright (c) 2022 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_SPINBOXDELEGATE_H
#define SATISFACTORY_PLANNER_SPINBOXDELEGATE_H

#include <QStyledItemDelegate>

#include "plan/Subfactory.h"

namespace ui {

class SpinBoxDelegate final : public QStyledItemDelegate {
	Q_OBJECT

  public:
	explicit SpinBoxDelegate(float min, float max, QObject* parent);

	QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const final;
	void setEditorData(QWidget* editor, const QModelIndex& index) const final;
	void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const final;
	void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const final;

  private:
	float spinbox_min_;
	float spinbox_max_;
};

} // namespace ui

#endif //SATISFACTORY_PLANNER_SPINBOXDELEGATE_H
