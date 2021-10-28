/**
 * @project Satisfactory_Planner
 * @file ProductionTable.cpp
 *
 * @author Jackson Miller
 * @date 2021-09-18
 * @copyright (c) 2021 Jackson Miller
 */

#include <QLabel>

#include "ProductionTable.h"

namespace ui {

ProductionTable::ProductionTable(plan::Subfactory &subfactory, std::shared_ptr<data::Library> db,
                                 QWidget *parent) :
                           subfactory_(subfactory),
                           db_(std::move(db)),
                           QWidget(parent) {
    layout_ = new QGridLayout(this);
}

void ProductionTable::initHeader() {
    auto done = new QLabel(tr("Done"), this);
    auto product = new QLabel(tr("Product"), this);
    auto recipe = new QLabel(tr("Recipe"), this);
    auto building = new QLabel(tr("Building"), this);
    auto power = new QLabel(tr("Power"), this);
    auto byproduct = new QLabel(tr("Byproduct"), this);
    auto ingredients = new QLabel(tr("Ingredients"), this);

    layout_->addWidget(done, 0, static_cast<int>(column::Checked), Qt::AlignCenter);
    layout_->addWidget(product, 0, static_cast<int>(column::Product), Qt::AlignCenter);
    layout_->addWidget(recipe, 0, static_cast<int>(column::Recipe), Qt::AlignCenter);
    layout_->addWidget(building, 0, static_cast<int>(column::Building), Qt::AlignCenter);
    layout_->addWidget(power, 0, static_cast<int>(column::Power), Qt::AlignCenter);
    layout_->addWidget(byproduct, 0, static_cast<int>(column::Byproduct), Qt::AlignCenter);
    layout_->addWidget(ingredients, 0, static_cast<int>(column::Ingredients), Qt::AlignLeft);
}

} // namespace ui
