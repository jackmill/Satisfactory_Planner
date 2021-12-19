/**
 * @project Satisfactory_Planner
 * @file ProductionTableModel.cpp
 * 
 * @author Jackson Miller
 * @date 2021-11-01
 * @copyright (c) 2021 Jackson Miller
 */

#include <QCheckBox>

#include <vector>
#include <algorithm>

#include "ProductionTableModel.h"
#include "ProductLineEditDialog.h"

namespace ui {

ProductionTableModel::ProductionTableModel(plan::Subfactory &subfactory, std::shared_ptr<data::Library> db, QObject *parent) :
    subfactory_(subfactory),
    db_(std::move(db)),
    QAbstractTableModel(parent) {

}

int ProductionTableModel::rowCount(const QModelIndex &parent) const {
    return subfactory_.product_lines_.size();
}

QVariant ProductionTableModel::data(const QModelIndex &index, int role) const {
    const auto product_line = subfactory_.product_lines_.at(index.row());
    const auto column = static_cast<Column> (index.column());

    if (role == Qt::ItemDataRole::DisplayRole) {
        if (column == Column::Checked) {
            return {};

        } else if (column == Column::Product) {
//            QString product = QString::fromStdString(product_line.target().name());
//            product += " : ";
//            product += QString::number(product_line.targetOutput());
//
//            return product;
            return {};

        } else if (column == Column::Recipe) {
            return QString::fromStdString(product_line.recipe().name());

        } else if (column == Column::Building) {
            QString building = QString::fromStdString(product_line.recipe().machine().name());
            building += " : ";
            building += QString::number(product_line.multiplier());

            return building;

        } else if (column == Column::Power) {
            float power = product_line.calcPower();
            return QString::number(power) + " MW";

        } else if (column == Column::Byproduct) {

            // Recipes can only produce a maximum of two products, so we just need to check that the recipe
            // in question produces two and then return whichever is not the targeted product
            std::vector<data::Item> product_list = product_line.calcProducts();
            if (product_list.size() > 1) {
                for (const auto &product : product_list) {
                    if (product != product_line.target()) {
                        QString byproduct = QString::fromStdString(product.name());
                        byproduct += " : ";
                        byproduct += QString::number(product.rate());

                        return byproduct;

                    }
                }
            } else {
                return {};
            }

        } else if (column == Column::Ingredients) {
            std::vector<data::Item> ingredient_list = product_line.calcIngredients();
            QString ingredients;

            for (const auto &ingredient : ingredient_list) {
                ingredients += QString::fromStdString(ingredient.name());
                ingredients += " : ";
                ingredients += QString::number(ingredient.rate());
                ingredients += " | ";
            }

            return ingredients;

        }
    }

    return {};

}

QVariant ProductionTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::ItemDataRole::DisplayRole || orientation != Qt::Horizontal) {
        return {};
    }

    const auto column = static_cast<Column> (section);
    switch (column) {
        case Column::Checked :      return tr("Done");
        case Column::Product :      return tr("Product");
        case Column::Recipe :       return tr("Recipe");
        case Column::Building :     return tr("Building");
        case Column::Power :        return tr("Power");
        case Column::Byproduct :    return tr("Byproduct");
        case Column::Ingredients :  return tr("Ingredients");
    }

    return {};
}

bool ProductionTableModel::insertRows(int startRow, int count, const QModelIndex &parent, data::Item &target) {
    if (subfactory_.targetRemainder(target) <= 0) {
        return false;
    }

    beginInsertRows(parent, startRow, startRow + count - 1);

    for (int row = startRow; row < startRow + count; ++row) {
        auto* dialog = new ProductLineEditDialog(db_->FindRecipes(target));
        if (dialog->exec() == QDialog::Accepted) {
            plan::ProductLine new_line = plan::ProductLine(target, dialog->getSelectedRecipe());

            subfactory_.product_lines_.emplace(subfactory_.product_lines_.cbegin(), new_line);
            subfactory_.updateIngredients();
            subfactory_.updateByproducts();
        }
        dialog->deleteLater();
    }

    endInsertRows();

    return true;
}

data::Item ProductionTableModel::getRowTarget(const QModelIndex &index) const {
    return subfactory_.product_lines_.at(index.row()).target();
}

}