/**
 * @project Satisfactory_Planner
 * @file ProductLineEditDialog.cpp
 * 
 * @author Jackson Miller
 * @date 2021-11-03
 * @copyright (c) 2021 Jackson Miller
 */

#include "ProductLineEditDialog.h"


namespace ui {

ProductLineEditDialog::ProductLineEditDialog(std::vector<data::Recipe> recipes, QWidget *parent) :
    recipes_(std::move(recipes)),
    QDialog(parent) {

    setWindowTitle(tr("Select Recipe"));
    layout_ = new QVBoxLayout(this);

    recipe_table_ = new QTableView(this);
    recipe_model_ = new RecipeSelectModel(recipes_, this);
    recipe_table_->setModel(recipe_model_);
    recipe_table_->setSelectionBehavior(QAbstractItemView::SelectRows);
    recipe_table_->resizeColumnsToContents();

    actions_ = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(actions_, &QDialogButtonBox::accepted, this, &ProductLineEditDialog::accept);
    connect(actions_, &QDialogButtonBox::rejected, this, &ProductLineEditDialog::reject);

    layout_->addWidget(recipe_table_);
    layout_->addWidget(actions_);

	setMinimumWidth(tableWidth());
}

data::Recipe ProductLineEditDialog::getSelectedRecipe() {
    if (recipe_table_->selectionModel()->hasSelection()) {
        return recipe_model_->getSelectedRecipe(recipe_table_->selectionModel()->currentIndex());
    } else {
        // Without a row selected, return the 'default' recipe
        // (The recipe named the same as the target product)
        for (const auto &recipe : recipes_) {
            for (const auto &product : recipe.productList()) {
                if (recipe.name() == product.name()) {
                    return recipe;
                }
            }
        }

        // Fall-through; if there is no recipe named the same as the target, return the first in the list
        return recipes_.at(0);
    }
}

int ProductLineEditDialog::tableWidth() const {
	int table_width = 0;

	for (int col = 0; col < ui::RecipeSelectModel::column_count; ++col) {
		table_width += recipe_table_->columnWidth(col);
	}

	return table_width;
}

}