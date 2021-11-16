/**
 * @project Satisfactory_Planner
 * @file ProductionPane.cpp
 * 
 * @author Jackson Miller
 * @date 2021-10-06
 * @copyright (c) 2021 Jackson Miller
 */

#include <QPushButton>
#include <QCheckBox>

#include "ProductionPane.h"
#include "ItemIconDelegate.h"
#include "CheckboxDelegate.h"
#include "../elements/ItemButton.h"
#include "../elements/ItemSelectionDialog.h"

namespace ui {

ProductionPane::ProductionPane(plan::Subfactory &subfactory, std::shared_ptr<data::Library> db,
                               QWidget *parent) :
                         subfactory_(subfactory),
                         db_(std::move(db)),
                         QWidget(parent) {
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

    updateByproducts();
    updateIngredients();
    updateTable();
}

void ProductionPane::initActions() {
    // Target List
    actions_.target_act_new = new QAction(tr("New Target"), this);
    connect(actions_.target_act_new,
            &QAction::triggered,
            this,
            [&] { targets_model_->insertRows(targets_model_->rowCount(QModelIndex()),
                                             1, QModelIndex()); });

    actions_.target_act_add_to_table = new QAction(tr("Add to Table"), this);
    connect(actions_.target_act_add_to_table,
            &QAction::triggered,
            this,
            [&] { table_model_->insertRows(table_model_->rowCount(QModelIndex()),
                                           1, QModelIndex(),
                                           targets_model_->getTarget(targets_->selectionModel()->currentIndex())); });

    actions_.target_act_del = new QAction(tr("Remove Target"), this);
    connect(actions_.target_act_del,
            &QAction::triggered,
            this,
            [&] { targets_model_->removeRows(targets_->selectionModel()->currentIndex().row(),
                                             1, QModelIndex()); });
}

void ProductionPane::initTargets() {
    targets_widget_ = new QGroupBox(tr("Products"), this);
    targets_layout_ = new QVBoxLayout(targets_widget_);

    targets_ = new QTableView(targets_widget_);
    targets_model_ = new TargetModel(db_, subfactory_, targets_widget_);
    targets_->setModel(targets_model_);

    targets_->setContextMenuPolicy(Qt::ActionsContextMenu);
    targets_->addAction(actions_.target_act_add_to_table);
    auto* target_spacer = new QAction(this);
    target_spacer->setSeparator(true);
    targets_->addAction(target_spacer);
    targets_->addAction(actions_.target_act_new);
    targets_->addAction(actions_.target_act_del);
    // TODO: Enable/Disable add to table


    if (subfactory_.product_targets_.empty()) {
        targets_model_->insertRows(targets_model_->rowCount(QModelIndex()), 1, QModelIndex());
    }

    targets_layout_->addWidget(targets_);
}

void ProductionPane::initByproducts() {
    byproducts_widget_ = new QGroupBox(tr("Byproducts"), this);
    byproducts_layout_ = new QVBoxLayout(byproducts_widget_);

    byproducts_ = new QTableView(byproducts_widget_);



    byproducts_layout_->addWidget(byproducts_);
}

void ProductionPane::initIngredients() {
    ingredients_widget_ = new QGroupBox(tr("Ingredients"), this);
    ingredients_layout_ = new QVBoxLayout(ingredients_widget_);

    ingredients_ = new QTableView(ingredients_widget_);
    ingredients_model_ = new IngredientsModel(subfactory_, ingredients_widget_);
    ingredients_->setModel(ingredients_model_);
    ingredients_->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ingredients_->setFocusPolicy(Qt::NoFocus);
    ingredients_->setSelectionMode(QAbstractItemView::NoSelection);

    ingredients_layout_->addWidget(ingredients_);
}

void ProductionPane::initTable() {
    production_table_ = new QTableView(this);
    table_model_ = new ProductionTableModel(subfactory_, db_, this);
    production_table_->setModel(table_model_);
    production_table_->resizeColumnsToContents();

    auto* done_check = new QCheckBox(production_table_);
    // connect(done_check, &QCheckbox::clicked, idk...
    auto* checkbox_delegate = new CheckboxDelegate(done_check, production_table_);
    production_table_->setItemDelegateForColumn(static_cast<int>(ProductionTableModel::Column::Checked),
                                                checkbox_delegate);

    auto* target_product_delegate = new ItemIconDelegate(this);
    production_table_->setItemDelegateForColumn(static_cast<int>(ProductionTableModel::Column::Product),
                                                target_product_delegate);
}

void ProductionPane::updateTable() {


}

void ProductionPane::updateByproducts() {

}

void ProductionPane::updateIngredients() {

}

bool ProductionPane::AddNewProductLineOk() {
    // If the currently selected target is NOT on the table
    if (subfactory_.targetRemainder(targets_model_->getTarget(targets_->selectionModel()->currentIndex())) > 0) {
        return true;
    }

    // If there is actually a target selected
    if (targets_->selectionModel()->hasSelection()) {
        return true;
    }

    return false;
}

}