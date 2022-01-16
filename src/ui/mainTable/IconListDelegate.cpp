/**
 * @project Satisfactory_Planner
 * @file IconListDelegate.cpp
 * 
 * @author Jackson Miller
 * @date 2022-01-10
 * @copyright (c) 2022 Jackson Miller
 */

#include <QPainter>

#include "IconListDelegate.h"
#include "IngredientIconList.h"
#include "../elements/TableIcon.h"

namespace ui {

IconListDelegate::IconListDelegate(plan::Subfactory_Ptr subfactory, QWidget* parent) :
	subfactory_(std::move(subfactory)),
	QStyledItemDelegate(parent) {
	assert(subfactory_);
}

void IconListDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const {
	const auto& line = (*subfactory_)->product_lines_.at(index.row());

	auto* ingredients_widget = new IngredientIconList(line.ingredients(), dynamic_cast<QWidget*>(parent()));
	ingredients_widget->setGeometry(option.rect);
	painter->save();
	painter->translate(option.rect.topLeft());
	ingredients_widget->render(painter);
	painter->restore();
}

QSize IconListDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const {
	const auto& line = (*subfactory_)->product_lines_.at(index.row());
	int width = static_cast<int>((ui::TableIcon::kSize_.width() + IngredientIconList::kPadding) * line.ingredients().size());

	return {width, ui::TableIcon::kSize_.height()};
}


}