/**
 * @project Satisfactory_Planner
 * @file RecipeIconList.cpp
 * 
 * @author Jackson Miller
 * @date 2022-01-10
 * @copyright (c) 2022 Jackson Miller
 */

#include "RecipeIconList.h"

namespace ui {

RecipeIconList::RecipeIconList(const std::vector<data::Item>& item_list, QWidget* parent) :
		QWidget(parent) {

	layout_ = new QHBoxLayout(this);
	layout_->setSpacing(kPadding);
	layout_->setContentsMargins(0, 0, 0, 0);
	layout_->setAlignment(Qt::AlignLeft);

	for (const auto& item : item_list) {
		auto* icon = new TableIcon(QString::fromStdString(item.name()),
		                           item.amount(),
		                           this);
		layout_->addWidget(icon);
	}
}

} // namespace ui