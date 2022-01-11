/**
 * @project Satisfactory_Planner
 * @file RecipeIconDelegate.cpp
 * 
 * @author Jackson Miller
 * @date 2022-01-10
 * @copyright (c) 2022 Jackson Miller
 */

#include <QPainter>

#include "RecipeIconDelegate.h"
#include "RecipeIconList.h"
#include "RecipeSelectModel.h"

namespace ui {

RecipeIconDelegate::RecipeIconDelegate(std::vector<data::Recipe> recipes, QWidget* parent) :
		recipes_(std::move(recipes)),
		QStyledItemDelegate(parent) {

}

void RecipeIconDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const {
	const auto& recipe = recipes_.at(index.row());
	const auto column = static_cast<RecipeSelectModel::Column>(index.column());

	if (column == RecipeSelectModel::Column::kIngredients) {
		auto* ingredients_widget = new RecipeIconList(recipe.ingredientList(), dynamic_cast<QWidget*>(parent()));
		ingredients_widget->setGeometry(option.rect);
		painter->save();
		painter->translate(option.rect.topLeft());
		ingredients_widget->render(painter);
		painter->restore();

		return;

	} else if (column == RecipeSelectModel::Column::kBuilding) {
		auto* building_icon = new TableIcon(QString::fromStdString(recipe.machine().name()),
											dynamic_cast<QWidget*>(parent()));
		building_icon->setGeometry(option.rect);
		painter->save();
		painter->translate(option.rect.topLeft());
		building_icon->render(painter);
		painter->restore();

		return;

	} else if (column == RecipeSelectModel::Column::kProducts) {
		auto* products_widget = new RecipeIconList(recipe.productList(), dynamic_cast<QWidget*>(parent()));
		products_widget->setGeometry(option.rect);
		painter->save();
		painter->translate(option.rect.topLeft());
		products_widget->render(painter);
		painter->restore();

		return;
	}
}

QSize RecipeIconDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const {
	const auto& recipe = recipes_.at(index.row());
	const auto column = static_cast<RecipeSelectModel::Column>(index.column());
	int width = static_cast<int>(ui::TableIcon::kSize_.width() + RecipeIconList::kPadding);

	if (column == RecipeSelectModel::Column::kIngredients) {
		width *= static_cast<int>(recipe.ingredientList().size());
	} else if (column == RecipeSelectModel::Column::kProducts) {
		width *= static_cast<int>(recipe.productList().size());
	} else {
		return ui::TableIcon::kSize_;
	}

	return {width, ui::TableIcon::kSize_.height()};
}


} // namespace ui