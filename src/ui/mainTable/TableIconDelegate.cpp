/**
 * @project Satisfactory_Planner
 * @file TableIconDelegate.cpp
 * 
 * @author Jackson Miller
 * @date 2022-01-01
 * @copyright (c) 2022 Jackson Miller
 */

#include <QPainter>

#include "../elements/TableIcon.h"
#include "../elements/BuildingTableIcon.h"
#include "TableIconDelegate.h"
#include "ProductionTableModel.h"

namespace ui {

TableIconDelegate::TableIconDelegate(plan::Subfactory** subfactory, QWidget* parent) :
	subfactory_(subfactory),
	QStyledItemDelegate(parent) {
	assert(subfactory_);
}

void TableIconDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const {
	std::unique_ptr<data::Item> button_item;

	const auto column = static_cast<ProductionTableModel::Column>(index.column());
	const auto& line = (*subfactory_)->productLineAt(index.row());

	if (column == ProductionTableModel::Column::Product) {
		button_item = std::make_unique<data::Item>(line->target()->target());
		button_item->setRate(line->target()->rate() * (line->percent() / 100));

	} else if (column == ProductionTableModel::Column::Byproduct) {
		if (line->hasByproduct()) {
			button_item = std::make_unique<data::Item>(line->byproduct());
		} else {
			return;
		}

	} else if (column == ProductionTableModel::Column::Building) {
		auto* icon = new BuildingTableIcon(QString::fromStdString(line->recipe().machine().name()),
		                           line->multiplier(),
		                           dynamic_cast<QWidget*>(parent()));
		icon->setGeometry(option.rect);
		painter->save();
		painter->translate(option.rect.topLeft());
		icon->render(painter);
		painter->restore();

		return;


	}

	auto* icon = new TableIcon(QString::fromStdString(button_item->name()),
	                           button_item->rate(),
	                           dynamic_cast<QWidget*>(parent()));
	icon->setGeometry(option.rect);
	painter->save();
	painter->translate(option.rect.topLeft());
	icon->render(painter);
	painter->restore();
}

QSize TableIconDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const {
	return ui::TableIcon::kSize_;
}

}