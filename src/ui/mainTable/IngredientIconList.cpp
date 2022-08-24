/**
 * @project Satisfactory_Planner
 * @file IngredientIconList.cpp
 * 
 * @author Jackson Miller
 * @date 2022-01-10
 * @copyright (c) 2022 Jackson Miller
 */

#include "IngredientIconList.h"
#include "../elements/TableIcon.h"

namespace ui {

IngredientIconList::IngredientIconList(const std::vector<data::Item>& ingredients_list, QWidget* parent) :
	QWidget(parent) {

	layout_ = new QHBoxLayout(this);
	layout_->setSpacing(kPadding);
	layout_->setContentsMargins(0, 0, 0, 0);
	layout_->setAlignment(Qt::AlignLeft);

	for (const auto& ingredient : ingredients_list) {
		auto* icon = new TableIcon(QString::fromStdString(ingredient.name()),
								   ingredient.rate(),
							  this);
		layout_->addWidget(icon);
	}
}

} // namespace ui