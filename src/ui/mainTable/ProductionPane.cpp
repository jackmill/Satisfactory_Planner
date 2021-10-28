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
    header_->setFixedHeight(85);
    header_layout_ = new QHBoxLayout(header_);
    header_layout_->setSpacing(5);

    targets_widget_ = new QGroupBox(tr("Products"), this);
    targets_ = new QHBoxLayout(targets_widget_);
    targets_->setMargin(0);

    byproducts_widget_ = new QGroupBox(tr("Byproducts"), this);
    byproducts_ = new QHBoxLayout(byproducts_widget_);
    byproducts_->setMargin(0);

    ingredients_widget_ = new QGroupBox(tr("Ingredients"), this);
    ingredients_ = new QHBoxLayout(ingredients_widget_);
    ingredients_->setMargin(0);

    header_layout_->addWidget(targets_widget_);
    header_layout_->addWidget(byproducts_widget_);
    header_layout_->addWidget(ingredients_widget_);

    production_widget_ = new QGroupBox(tr("Production"), this);
    production_table_ = new ProductionTable(subfactory_, db, production_widget_);

    layout_->addWidget(header_);
    layout_->addWidget(production_widget_);

    updateTargets();
    updateByproducts();
    updateIngredients();
    updateTable();
}

void ProductionPane::updateTable() {


}

void ProductionPane::updateTargets() {
    // Remove existing buttons
    QLayoutItem* child;
    while ((child = targets_->takeAt(0)) != nullptr) {
        child->widget()->deleteLater();
        delete child;
    }

    // Populate list
    for (auto &target : subfactory_.product_targets_) {
        targets_->addWidget(new ItemButton(target, db_, targets_widget_));
    }

    // Add 'Add new' button to end
    auto add_button = new QPushButton(QIcon(":/gui/plus.png"), "", targets_widget_);
    auto plus_size = new QSize(45, 45);
    add_button->setFixedSize(*plus_size);
    add_button->setIconSize(*plus_size * 0.8);

    targets_->addWidget(add_button);
    connect(add_button, &QPushButton::clicked, this, &ProductionPane::addTarget);
}

void ProductionPane::updateByproducts() {

}

void ProductionPane::updateIngredients() {

}

void ProductionPane::addTarget() {
    auto dialog = new ItemSelectionDialog(db_, this);
    dialog->deleteLater();
    if (dialog->exec() == QDialog::Accepted) {
        data::Item new_target = data::Item(dialog->getSelectedItem());
        new_target.setAmount(dialog->getAmount());

        // Look through the targets and make sure we aren't adding a duplicate target
        // If we are, add the requested amount to the existing target
        for (auto &existing_target : subfactory_.product_targets_) {
            if (existing_target == new_target) {
                existing_target.setAmount(existing_target.amount() + new_target.amount());
                updateTargets();
                return;
            }
        }

        // If we're here it's because this is a new item
        subfactory_.addTarget(new_target);
        updateTargets();
    }
}

}