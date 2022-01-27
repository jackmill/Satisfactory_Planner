/**
 * @project Satisfactory_Planner
 * @file SpinBoxDelegate.cpp
 * 
 * @author Jackson Miller
 * @date 2022-01-01
 * @copyright (c) 2022 Jackson Miller
 */

#include <QDoubleSpinBox>
#include <QPushButton>

#include "SpinBoxDelegate.h"
#include "ProductionTableModel.h"

namespace ui {

SpinBoxDelegate::SpinBoxDelegate(float min, float max, QObject* parent) :
		QStyledItemDelegate(parent),
		spinbox_min_(min),
		spinbox_max_(max) {

}

QWidget* SpinBoxDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const {
	auto* editor = new QDoubleSpinBox(parent);
	editor->setFrame(false);
	editor->setMinimum(spinbox_min_);
	editor->setMaximum(spinbox_max_);

	return editor;
}

void SpinBoxDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const {
	float value = index.model()->data(index, Qt::EditRole).toFloat();

	auto* spin_box = dynamic_cast<QDoubleSpinBox*>(editor);
	spin_box->setValue(value);
}

void SpinBoxDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const {
	auto* spin_box = dynamic_cast<QDoubleSpinBox*>(editor);
	spin_box->interpretText();
	auto value = static_cast<float>(spin_box->value());

	model->setData(index, value, Qt::EditRole);
}

void SpinBoxDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option,
                                           const QModelIndex& index) const {
	editor->setGeometry(option.rect);
}


}