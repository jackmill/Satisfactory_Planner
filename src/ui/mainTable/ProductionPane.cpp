/**
 * @project Satisfactory_Planner
 * @file ProductionPane.cpp
 * 
 * @author Jackson Miller
 * @date 2021-10-06
 * @copyright (c) 2021 Jackson Miller
 */

#include <QPushButton>

#include "ProductionPane.h"
#include "recipeSelectDialog/ProductLineEditDialog.h"
#include "../elements/ItemSelectionDialog.h"
#include "../elements/TableIcon.h"
#include "SpinBoxDelegate.h"
#include "TableIconDelegate.h"
#include "IconListDelegate.h"

namespace ui {

ProductionPane::ProductionPane(std::shared_ptr<plan::Subfactory> subfactory, std::shared_ptr<data::Library> db,
                               QWidget *parent) :
                         subfactory_(std::move(subfactory)),
                         db_(std::move(db)),
                         QWidget(parent) {
    assert(subfactory_);
    assert(db_);

    layout_ = new QVBoxLayout(this);
    header_ = new QWidget(this);
    header_layout_ = new QHBoxLayout(header_);
    header_layout_->setSpacing(5);

    initActions();
    initTargets();
    initIngredients();
    initByproducts();

    header_layout_->addWidget(targets_widget_);
    header_layout_->addWidget(byproducts_widget_);
    header_layout_->addWidget(ingredients_widget_);

    initTable();

    layout_->addWidget(header_);
    layout_->addWidget(production_table_);
}

void ProductionPane::initActions() {
    // Target List
    actions_.target_act_new = new QAction(tr("New Target"), this);
    connect(actions_.target_act_new,
            &QAction::triggered,
            this,
            &ProductionPane::S_addNewTarget);

    actions_.target_act_add_to_table = new QAction(tr("Add to Table"), this);
    connect(actions_.target_act_add_to_table,
            &QAction::triggered,
            this,
            [&] { S_addToTable(targets_model_->getTarget(targets_->selectionModel()->currentIndex())); });


    actions_.target_act_edit = new QAction(tr("Edit Target"), this);
    connect(actions_.target_act_edit,
            &QAction::triggered,
            this,
            [&] { S_editTarget(targets_->selectionModel()->currentIndex()); });

    actions_.target_act_del = new QAction(tr("Remove Target"), this);
    connect(actions_.target_act_del,
            &QAction::triggered,
            this,
            [&] { S_removeTarget(targets_->selectionModel()->currentIndex()); });

    actions_.ingredient_act_add_to_table = new QAction(tr("Add to Table"), this);
    connect(actions_.ingredient_act_add_to_table,
            &QAction::triggered,
            this,
            [&] { S_addToTable(ingredients_model_->getTarget(ingredients_->selectionModel()->currentIndex())); });
}

void ProductionPane::initTargets() {
    targets_widget_ = new QGroupBox(tr("Products"), this);
    targets_layout_ = new QVBoxLayout(targets_widget_);

    targets_ = new QTableView(targets_widget_);
    targets_model_ = new TargetModel(db_, subfactory_, targets_widget_);
    targets_->setModel(targets_model_);
    targets_->resizeColumnsToContents();

	auto* target_spinbox = new SpinBoxDelegate(0.01, 99999.0, this);
	targets_->setItemDelegateForColumn(static_cast<int>(TargetModel::Column::kRate), target_spinbox);

    targets_->setContextMenuPolicy(Qt::ActionsContextMenu);

	targets_->addAction(actions_.target_act_new);
    auto* target_spacer = new QAction(this);
    target_spacer->setSeparator(true);
	targets_->addAction(target_spacer);

	targets_->addAction(actions_.target_act_add_to_table);
	targets_->addAction(actions_.target_act_edit);
	targets_->addAction(actions_.target_act_del);

    targets_layout_->addWidget(targets_);

	connect(targets_->selectionModel(), &QItemSelectionModel::selectionChanged, this, &ProductionPane::S_targetSelectionChanged);

    connect(targets_model_, &TargetModel::dataChanged, this, &ProductionPane::S_refreshAll);
    connect(targets_model_, &TargetModel::rowsInserted, this, &ProductionPane::S_factoryChanged);
    connect(targets_model_, &TargetModel::rowsRemoved, this, &ProductionPane::S_factoryChanged);
    connect(targets_model_, &TargetModel::modelReset, this, &ProductionPane::S_factoryChanged);
}

void ProductionPane::initByproducts() {
    byproducts_widget_ = new QGroupBox(tr("Byproducts"), this);
    byproducts_layout_ = new QVBoxLayout(byproducts_widget_);

    byproducts_ = new QTableView(byproducts_widget_);
    byproducts_model_ = new SubfacItemListModel(subfactory_->byproducts_, byproducts_widget_);
    byproducts_->setModel(byproducts_model_);
    byproducts_->setSelectionMode(QAbstractItemView::NoSelection);


    byproducts_layout_->addWidget(byproducts_);
}

void ProductionPane::initIngredients() {
    ingredients_widget_ = new QGroupBox(tr("Ingredients"), this);
    ingredients_layout_ = new QVBoxLayout(ingredients_widget_);

    ingredients_ = new QTableView(ingredients_widget_);
    ingredients_model_ = new SubfacItemListModel(subfactory_->ingredientsNotOnTable(), ingredients_widget_);
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

void ProductionPane::S_addNewTarget() {
    auto *dialog = new ItemSelectionDialog(db_, this);
    if (dialog->exec() == QDialog::Accepted) {
        data::Item new_target = dialog->getSelectedItem();

        // Check that this isn't a duplicate target
        bool duplicate = false;
        for (auto &existing_item : subfactory_->targets_) {
            if (new_target == *existing_item) {
                existing_item->setRate(existing_item->rate() + new_target.rate());
                duplicate = true;
            }
        }

        if (!duplicate) {
            targets_model_->insertRows(targets_model_->rowCount(QModelIndex()), QModelIndex(), std::make_shared<data::Item> (new_target));
        }

        targets_->resizeColumnsToContents();
    }
    dialog->deleteLater();
}

void ProductionPane::S_editTarget(const QModelIndex &index) {
    std::shared_ptr<data::Item> item = targets_model_->getTarget(index);
    auto* dialog = new ItemSelectionDialog(*item, db_, this);
	dialog->allowItemChange(!subfactory_->isTarget(item));
    if (dialog->exec() == QDialog::Accepted) {
        data::Item new_target = dialog->getSelectedItem();

        // If we're creating a duplicate target, add the edited rate to the existing and get rid of the duplicate
        bool duplicate = false;
        for (auto existing_item = subfactory_->targets_.cbegin(); existing_item != subfactory_->targets_.cend(); ++existing_item) {
            if (new_target == **existing_item &&
                index.row() != std::distance(subfactory_->targets_.cbegin(), existing_item)) {
                duplicate = true;
                (*existing_item)->setRate((*existing_item)->rate() + new_target.rate());
                targets_model_->removeRows(index.row(), 1, QModelIndex());
            }
        }

        if (!duplicate) {
            item->replaceWith(new_target);
        }

        if (subfactory_->isTarget(item)) {
			Q_EMIT(targets_model_->dataChanged(index, index));
        }

        targets_->resizeColumnsToContents();
    }
    dialog->deleteLater();
}

void ProductionPane::S_removeTarget(const QModelIndex& index) {
    // Find and eliminate the product line that the product is tied to
    if (!subfactory_->product_lines_.empty()) {
        auto target_item = subfactory_->targets_.at(index.row());
        for (auto product_line = subfactory_->product_lines_.cbegin();
             product_line != subfactory_->product_lines_.cend();
             ++product_line) {
            if (target_item == product_line->target()) {
                subfactory_->product_lines_.erase(product_line);
            }
        }
        table_model_->refreshModel();
    }

    // Remove the target
    targets_model_->removeRows(index.row(), 1, QModelIndex());

    // Refresh the rest of the table
    ingredients_model_->refreshModel(subfactory_->ingredientsNotOnTable());
}

void ProductionPane::S_addToTable(std::shared_ptr<data::Item> target) {
    // TODO: Split target lines -- lines with the same target need to sum to 100%
	if (subfactory_->targetRemainder(target) > 0) {
        const auto recipes = db_->FindRecipes(*target);
        bool added_to_table = false;

        // If there's only one recipe to choose, just select that one
        if (recipes.size() == 1) {
            table_model_->insertRows(table_model_->rowCount(QModelIndex()),
                                     QModelIndex(),
                                     plan::ProductLine(std::move(target), recipes.at(0)));
            production_table_->setRowHeight(table_model_->rowCount(QModelIndex()), ui::TableIcon::kSize_.height());
			added_to_table = true;
        }

        // If there's more than one, prompt user to choose recipe
        if (!added_to_table) {
            auto *dialog = new ProductLineEditDialog(recipes);
            if (dialog->exec() == QDialog::Accepted) {
                table_model_->insertRows(table_model_->rowCount(QModelIndex()),
                                         QModelIndex(),
                                         plan::ProductLine(std::move(target), dialog->getSelectedRecipe()));
	            production_table_->setRowHeight(table_model_->rowCount(QModelIndex()), ui::TableIcon::kSize_.height());
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
	subfactory_->calculate();

	targets_model_->refreshModel();
	table_model_->refreshModel();
	byproducts_model_->refreshModel();
	ingredients_model_->refreshModel(subfactory_->ingredientsNotOnTable());

	resizeAll();
}

void ProductionPane::S_targetSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected) {
	if (selected.empty()) {
		actions_.target_act_add_to_table->setEnabled(false);
		actions_.target_act_edit->setEnabled(false);
		actions_.target_act_del->setEnabled(false);
		actions_.target_act_new->setEnabled(true);
		return;
	}

	const auto selected_target = targets_model_->getTarget(selected.indexes().at(0));
	if (subfactory_->isTarget(selected_target)) {
		actions_.target_act_add_to_table->setEnabled(false);
		actions_.target_act_del->setEnabled(false);
		actions_.target_act_edit->setEnabled(true);
		actions_.target_act_new->setEnabled(true);
		return;
	} else {
		actions_.target_act_add_to_table->setEnabled(true);
		actions_.target_act_del->setEnabled(true);
		actions_.target_act_edit->setEnabled(true);
		actions_.target_act_new->setEnabled(true);
		return;
	}
}

}