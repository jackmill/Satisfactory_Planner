/**
 * @project Satisfactory_Planner
 * @file ItemIconDelegate.cpp
 * 
 * @author Jackson Miller
 * @date 2022-01-01
 * @copyright (c) 2022 Jackson Miller
 */

#include <QPainter>

#include "../elements/ItemIcon.h"
#include "ItemIconDelegate.h"
#include "ProductionTableModel.h"

namespace ui {

ItemIconDelegate::ItemIconDelegate(std::shared_ptr<plan::Subfactory> subfactory, QObject* parent) :
	subfactory_(std::move(subfactory)),
	QStyledItemDelegate(parent) {
	assert(subfactory_);
}

void ItemIconDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const {
	std::shared_ptr<data::Item> button_item;
	const auto column = static_cast<ProductionTableModel::Column>(index.column());
	const auto& line = subfactory_->product_lines_.at(index.row());

	if (column == ProductionTableModel::Column::Product) {
		button_item = line.target();
		//TODO: Doesn't update to reflect percentage changes

	} else if (column == ProductionTableModel::Column::Byproduct) {
		if (line.hasByproduct()) {
			button_item = std::make_shared<data::Item>(line.byproduct());
		} else {
			return;
		}

	} else if (column == ProductionTableModel::Column::Ingredient1) {
		button_item = std::make_shared<data::Item>(line.ingredients().at(0));

	} else if (column == ProductionTableModel::Column::Ingredient2) {
		if (line.ingredients().size() >= 2) {
			button_item = std::make_shared<data::Item>(line.ingredients().at(1));
		} else {
			return;
		}

	} else if (column == ProductionTableModel::Column::Ingredient3) {
		if (line.ingredients().size() >= 3) {
			button_item = std::make_shared<data::Item>(line.ingredients().at(2));
		} else {
			return;
		}

	} else if (column == ProductionTableModel::Column::Ingredient4) {
		if (line.ingredients().size() >= 4) {
			button_item = std::make_shared<data::Item>(line.ingredients().at(3));
		} else {
			return;
		}

	}

	auto* icon = new ItemIcon(button_item);
	icon->setGeometry(option.rect);
	painter->save();
	painter->translate(option.rect.topLeft());
	icon->render(painter);
	painter->restore();
}

QSize ItemIconDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const {
	return ui::ItemIcon::kSize_;
}

}