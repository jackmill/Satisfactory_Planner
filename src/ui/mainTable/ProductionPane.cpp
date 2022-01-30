/**
 * @project Satisfactory_Planner
 * @file ProductionPane.cpp
 * 
 * @author Jackson Miller
 * @date 2021-10-06
 * @copyright (c) 2021 Jackson Miller
 */

#include <QPushButton>
#include <utility>

#include "ProductionPane.h"
#include "RecipeSelectDialog/RecipeSelectDialog.h"
#include "PercentEditDialog/PercentEditDialog.h"
#include "ClockSpeedEditDialog/ClockSpeedEditDialog.h"
#include "../elements/ItemSelectionDialog.h"
#include "../elements/TableIcon.h"
#include "SpinBoxDelegate.h"
#include "TableIconDelegate.h"
#include "IconListDelegate.h"

namespace ui {

ProductionPane::ProductionPane(const std::shared_ptr<plan::Subfactory>& subfactory, std::shared_ptr<data::Library> db,
                               QWidget *parent) :
                         subfactory_(std::make_shared<std::shared_ptr<plan::Subfactory>>(subfactory)),
                         db_(std::move(db)),
                         QWidget(parent) {
    assert(subfactory_);
    assert(db_);

    layout_ = new QVBoxLayout(this);
    header_ = new QWidget(this);
    header_layout_ = new QHBoxLayout(header_);
    header_layout_->setSpacing(5);

    initActions();
	initProducts();
    initIngredients();
    initByproducts();

    header_layout_->addWidget(products_widget_);
    header_layout_->addWidget(byproducts_widget_);
    header_layout_->addWidget(ingredients_widget_);

    initTable();

    layout_->addWidget(header_);
    layout_->addWidget(production_table_);

	resizeAll();
}

void ProductionPane::initActions() {
    // Target List
    actions_.product_act_new = new QAction(tr("New Target"), this);
    connect(actions_.product_act_new,
            &QAction::triggered,
            this,
            &ProductionPane::S_addNewTarget);

    actions_.product_act_add_to_table = new QAction(tr("Add to Table"), this);
    connect(actions_.product_act_add_to_table,
            &QAction::triggered,
            [this] { S_addToTable(products_model_->getTarget(products_->selectionModel()->currentIndex())); });


    actions_.product_act_edit = new QAction(tr("Edit Target"), this);
    connect(actions_.product_act_edit,
            &QAction::triggered,
            [this] { S_editTarget(products_->selectionModel()->currentIndex()); });

    actions_.product_act_del = new QAction(tr("Remove Target"), this);
    connect(actions_.product_act_del,
            &QAction::triggered,
            [this] { S_removeTarget(products_->selectionModel()->currentIndex()); });

    actions_.ingredient_act_add_to_table = new QAction(tr("Add to Table"), this);
    connect(actions_.ingredient_act_add_to_table,
            &QAction::triggered,
            [this] { S_addToTable(ingredients_model_->getTarget(ingredients_->selectionModel()->currentIndex())); });
	
	if ((*subfactory_)->products_.empty()) {
		actions_.product_act_add_to_table->setEnabled(false);
		actions_.product_act_edit->setEnabled(false);
		actions_.product_act_del->setEnabled(false);
		actions_.product_act_new->setEnabled(true);
	}

	// Production Table
	prod_table_actions_.recipe_change = new QAction(tr("Change Recipe..."), this);
	connect(prod_table_actions_.recipe_change,
			&QAction::triggered,
			[this] { S_changeProductLineRecipe(production_table_->selectionModel()->currentIndex()); });

	prod_table_actions_.percent_edit = new QAction(tr("Line Percentage..."), this);
	connect(prod_table_actions_.percent_edit,
			&QAction::triggered,
			[this] { S_editPercent(production_table_->selectionModel()->currentIndex()); });

	prod_table_actions_.clock_edit = new QAction(tr("Clock Speed..."), this);
	connect(prod_table_actions_.clock_edit,
			&QAction::triggered,
			[this] { S_editClockSpeed(production_table_->selectionModel()->currentIndex()); });

	prod_table_actions_.byproduct_use = new QAction(tr("Reuse Byproduct"), this);
	prod_table_actions_.byproduct_use->setCheckable(true);
	connect(prod_table_actions_.byproduct_use,
			&QAction::toggled,
			[this] (bool checked){
		(*subfactory_)->product_lines_.at(production_table_->selectionModel()->currentIndex().row()).setUseByproduct(checked);
	});

	prod_table_actions_.delete_row = new QAction(tr("Delete Row"), this);
	connect(prod_table_actions_.delete_row,
			&QAction::triggered,
			[this] { S_removeProductLine(production_table_->selectionModel()->currentIndex()); });

}

void ProductionPane::initProducts() {
	products_widget_ = new QGroupBox(tr("Products"), this);
	products_layout_ = new QVBoxLayout(products_widget_);

	products_ = new QTableView(products_widget_);
	products_model_ = new ProductModel(db_, subfactory_, products_widget_);
    products_->setModel(products_model_);
    products_->resizeColumnsToContents();

	auto* target_spinbox = new SpinBoxDelegate(0.01, 99999.0, this);
	products_->setItemDelegateForColumn(static_cast<int>(ProductModel::Column::kRate), target_spinbox);

    products_->setContextMenuPolicy(Qt::ActionsContextMenu);

	products_->addAction(actions_.product_act_new);
    auto* product_spacer = new QAction(this);
    product_spacer->setSeparator(true);
	products_->addAction(product_spacer);

	products_->addAction(actions_.product_act_add_to_table);
	products_->addAction(actions_.product_act_edit);
	products_->addAction(actions_.product_act_del);

    products_layout_->addWidget(products_);

	connect(products_->selectionModel(),
			&QItemSelectionModel::selectionChanged,
			this,
	        &ProductionPane::S_productSelectionChanged);

    connect(products_model_, &ProductModel::dataChanged, this, &ProductionPane::S_refreshAll);
    connect(products_model_, &ProductModel::rowsInserted, this, &ProductionPane::S_factoryChanged);
    connect(products_model_, &ProductModel::rowsRemoved, this, &ProductionPane::S_factoryChanged);
    connect(products_model_, &ProductModel::modelReset, this, &ProductionPane::S_factoryChanged);
}

void ProductionPane::initByproducts() {
    byproducts_widget_ = new QGroupBox(tr("Byproducts"), this);
    byproducts_layout_ = new QVBoxLayout(byproducts_widget_);

    byproducts_ = new QTableView(byproducts_widget_);
    byproducts_model_ = new SubfacItemListModel((*subfactory_)->byproducts_, byproducts_widget_);
    byproducts_->setModel(byproducts_model_);
    byproducts_->setSelectionMode(QAbstractItemView::NoSelection);


    byproducts_layout_->addWidget(byproducts_);
}

void ProductionPane::initIngredients() {
    ingredients_widget_ = new QGroupBox(tr("Ingredients"), this);
    ingredients_layout_ = new QVBoxLayout(ingredients_widget_);

    ingredients_ = new QTableView(ingredients_widget_);
    ingredients_model_ = new SubfacItemListModel((*subfactory_)->ingredientsNotOnTable(), ingredients_widget_);
    ingredients_->setModel(ingredients_model_);
    ingredients_->setSelectionBehavior(QAbstractItemView::SelectRows);

    ingredients_->setContextMenuPolicy(Qt::ActionsContextMenu);
    ingredients_->addAction(actions_.ingredient_act_add_to_table);

    ingredients_layout_->addWidget(ingredients_);
}

void ProductionPane::initTable() {
    production_table_ = new QTableView(this);
    table_model_ = new ProductionTableModel(subfactory_, db_, this);
    production_table_->setModel(table_model_);

	auto* single_icon_delegate = new TableIconDelegate(subfactory_, this);
	production_table_->setItemDelegateForColumn(static_cast<int>(ProductionTableModel::Column::Product),
	                                            single_icon_delegate);
	production_table_->setItemDelegateForColumn(static_cast<int>(ProductionTableModel::Column::Building),
	                                            single_icon_delegate);
	production_table_->setItemDelegateForColumn(static_cast<int>(ProductionTableModel::Column::Byproduct),
	                                            single_icon_delegate);

	auto* percentage_delegate = new SpinBoxDelegate(0.01, 100.0, this);
	production_table_->setItemDelegateForColumn(static_cast<int>(ProductionTableModel::Column::Percentage),
												percentage_delegate);

	auto* clock_speed_delegate = new SpinBoxDelegate(0.01, 250.0, this);
	production_table_->setItemDelegateForColumn(static_cast<int>(ProductionTableModel::Column::ClockSpeed),
	                                            clock_speed_delegate);

	production_table_->setContextMenuPolicy(Qt::ActionsContextMenu);
	production_table_->addAction(prod_table_actions_.recipe_change);
	production_table_->addAction(prod_table_actions_.percent_edit);
	production_table_->addAction(prod_table_actions_.clock_edit);
	production_table_->addAction(prod_table_actions_.byproduct_use);
	auto* prod_table_context_spacer = new QAction(this);
	prod_table_context_spacer->setSeparator(true);
	production_table_->addAction(prod_table_context_spacer);
	production_table_->addAction(prod_table_actions_.delete_row);
	connect(production_table_->selectionModel(),
			&QItemSelectionModel::selectionChanged,
			[this] { S_prodTableContextMenu(production_table_->selectionModel()->currentIndex()); });

	auto* ingredients_delegate = new IconListDelegate(subfactory_, this);
	production_table_->setItemDelegateForColumn(static_cast<int>(ProductionTableModel::Column::Ingredients),
												ingredients_delegate);

	connect(table_model_, &ProductionTableModel::dataChanged, this, &ProductionPane::S_refreshAll);
    connect(table_model_, &ProductionTableModel::rowsInserted, this, &ProductionPane::S_factoryChanged);
    connect(table_model_, &ProductionTableModel::rowsRemoved, this, &ProductionPane::S_factoryChanged);
    connect(table_model_, &ProductionTableModel::modelReset, this, &ProductionPane::S_factoryChanged);
}

void ProductionPane::resizeAll() {
    production_table_->resizeColumnsToContents();
	production_table_->resizeRowsToContents();
    byproducts_->resizeColumnsToContents();
    ingredients_->resizeColumnsToContents();
}

void ProductionPane::changeSubfactory(std::shared_ptr<plan::Subfactory> subfactory) {
	*subfactory_ = std::move(subfactory);

	S_refreshAll();
}

void ProductionPane::S_addNewTarget() {
    auto *dialog = new ItemSelectionDialog(db_, this);
    if (dialog->exec() == QDialog::Accepted) {
        data::Item new_target = dialog->getSelectedItem();

        // Check that this isn't a duplicate target
        bool duplicate = false;
        for (auto &existing_item : (*subfactory_)->products_) {
            if (new_target == existing_item->target()) {
                existing_item->setRate(existing_item->rate() + new_target.rate());
                duplicate = true;
            }
        }

        if (!duplicate) {
            products_model_->insertRows(products_model_->rowCount(QModelIndex()),
                                        QModelIndex(),
                                        std::make_shared<plan::LineTarget> (new_target));
        }

        products_->resizeColumnsToContents();
    }
    dialog->deleteLater();
}

void ProductionPane::S_editTarget(const QModelIndex &index) {
    std::shared_ptr<plan::LineTarget> item = products_model_->getTarget(index);
    auto* dialog = new ItemSelectionDialog(item->target(), db_, this);
	dialog->allowItemChange(!(*subfactory_)->isOnTable(item));
    if (dialog->exec() == QDialog::Accepted) {
        data::Item new_target = dialog->getSelectedItem();

        // If we're creating a duplicate target, add the edited rate to the existing and get rid of the duplicate
        bool duplicate = false;
        for (auto existing_item = (*subfactory_)->products_.cbegin(); existing_item != (*subfactory_)->products_.cend(); ++existing_item) {
            if (new_target == (*existing_item)->target() &&
                index.row() != std::distance((*subfactory_)->products_.cbegin(), existing_item)) {
                duplicate = true;
                (*existing_item)->setRate((*existing_item)->rate() + new_target.rate());
                products_model_->removeRows(index.row(), 1, QModelIndex());
            }
        }

        if (!duplicate) {
            item->replaceWith(new_target);
        }

        if ((*subfactory_)->isOnTable(item)) {
			Q_EMIT(products_model_->dataChanged(index, index));
        }

        products_->resizeColumnsToContents();
    }
    dialog->deleteLater();
}

void ProductionPane::S_removeTarget(const QModelIndex& index) {
    // Remove the product
    products_model_->removeRows(index.row(), 1, QModelIndex());

    // Refresh the rest of the table
    ingredients_model_->refreshModel((*subfactory_)->ingredientsNotOnTable());
}

void ProductionPane::S_addToTable(std::shared_ptr<plan::LineTarget> target) {
	if ((*subfactory_)->productRemainder(target) > 0) {
        const auto recipes = db_->FindRecipes(target->target());
        bool added_to_table = false;
		float new_line_percent = 100 - target->completion();

        // If there's only one recipe to choose, just select that one
        if (recipes.size() == 1) {
			auto new_line = plan::ProductLine(std::move(target), recipes.at(0));
			new_line.setPercent(new_line_percent);

			table_model_->insertRows(table_model_->rowCount(QModelIndex()),
                                     QModelIndex(),
                                     new_line);
			added_to_table = true;
        }

        // If there's more than one, prompt user to choose recipe
        if (!added_to_table) {
            auto *dialog = new RecipeSelectDialog(recipes);
            if (dialog->exec() == QDialog::Accepted) {
				auto new_line = plan::ProductLine(std::move(target), dialog->getSelectedRecipe());
	            new_line.setPercent(new_line_percent);

				table_model_->insertRows(table_model_->rowCount(QModelIndex()),
                                         QModelIndex(),
                                         new_line);
				added_to_table = true;
            }
            dialog->deleteLater();
        }

        // Finish up the addition, but only if the recipe has been added to the table
        if (added_to_table) {
	        S_refreshAll();
        }
    }
}

void ProductionPane::S_refreshAll() {
	(*subfactory_)->calculate();

	products_model_->refreshModel();
	table_model_->refreshModel();
	byproducts_model_->refreshModel();
	ingredients_model_->refreshModel((*subfactory_)->ingredientsNotOnTable());

	resizeAll();
}

void ProductionPane::S_productSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected) {
	if (selected.empty() || (*subfactory_)->products_.empty()) {
		actions_.product_act_add_to_table->setEnabled(false);
		actions_.product_act_edit->setEnabled(false);
		actions_.product_act_del->setEnabled(false);
		actions_.product_act_new->setEnabled(true);
		return;
	}

	const auto selected_target = products_model_->getTarget(selected.indexes().at(0));
	if ((*subfactory_)->isOnTable(selected_target)) {
		if (selected_target->completion() >= 100.0) {
			actions_.product_act_add_to_table->setEnabled(false);
		} else {
			actions_.product_act_add_to_table->setEnabled(true);
		}
		actions_.product_act_del->setEnabled(false);
		actions_.product_act_edit->setEnabled(true);
		actions_.product_act_new->setEnabled(true);
		return;
	} else {
		actions_.product_act_add_to_table->setEnabled(true);
		actions_.product_act_del->setEnabled(true);
		actions_.product_act_edit->setEnabled(true);
		actions_.product_act_new->setEnabled(true);
		return;
	}
}

void ProductionPane::S_prodTableContextMenu(const QModelIndex& index) {
	prod_table_actions_.setAllInvisible();

	const auto& selected_line = (*subfactory_)->product_lines_.at(index.row());
	if (!selected_line.isChangeable()) {
		prod_table_actions_.delete_row->setEnabled(false);
		prod_table_actions_.delete_row->setToolTip(tr("Cannot delete product line whose ingredients are used by the table"));

		prod_table_actions_.recipe_change->setEnabled(false);
		prod_table_actions_.recipe_change->setToolTip(tr("Cannot change product line whose ingredients are used by the table"));
	} else {
		prod_table_actions_.delete_row->setEnabled(true);
		prod_table_actions_.delete_row->setToolTip("");

		if (db_->FindRecipes(selected_line.target()->target()).size() <= 1) {
			prod_table_actions_.recipe_change->setEnabled(false);
			prod_table_actions_.recipe_change->setToolTip(tr("No other recipes available"));
		} else {
			prod_table_actions_.recipe_change->setEnabled(true);
			prod_table_actions_.recipe_change->setToolTip("");
		}

	}

	const auto column = static_cast<ProductionTableModel::Column>(index.column());
	if (column == ProductionTableModel::Column::Recipe) {
		prod_table_actions_.recipe_change->setVisible(true);
	} else if (column == ProductionTableModel::Column::Percentage) {
		prod_table_actions_.percent_edit->setVisible(true);
	} else if (column == ProductionTableModel::Column::ClockSpeed) {
		prod_table_actions_.clock_edit->setVisible(true);
	} else if (column == ProductionTableModel::Column::Byproduct) {
		prod_table_actions_.byproduct_use->setVisible(true);
	}
}

void ProductionPane::S_editPercent(const QModelIndex& index) {
	auto* dialog = new PercentEditDialog((*subfactory_)->product_lines_.at(index.row()), this);
	if (dialog->exec() == QDialog::Accepted) {
		(*subfactory_)->product_lines_.at(index.row()).setPercent(dialog->selectedPercent());
		S_refreshAll();
	}
	dialog->deleteLater();
}

void ProductionPane::S_editClockSpeed(const QModelIndex& index) {
	auto* dialog = new ClockSpeedEditDialog((*subfactory_)->product_lines_.at(index.row()), this);
	if (dialog->exec() == QDialog::Accepted) {
		(*subfactory_)->product_lines_.at(index.row()).setClock(dialog->getNewMult());
		S_refreshAll();
	}
	dialog->deleteLater();
}

void ProductionPane::S_removeProductLine(const QModelIndex& index) {
	table_model_->removeRows(index.row(), 1, QModelIndex());

	// Refresh the rest of the table
	S_refreshAll();
}

void ProductionPane::S_changeProductLineRecipe(const QModelIndex& index) {
	const auto recipes = db_->FindRecipes((*subfactory_)->product_lines_.at(index.row()).target()->target());
	auto* dialog = new RecipeSelectDialog(recipes);
	if (dialog->exec() == QDialog::Accepted) {
		(*subfactory_)->product_lines_.at(index.row()).changeRecipe(dialog->getSelectedRecipe());
		S_refreshAll();
	}
	dialog->deleteLater();
}

}