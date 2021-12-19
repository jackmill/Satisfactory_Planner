/**
 * @project Satisfactory_Planner
 * @file TargetModel.cpp
 * 
 * @author Jackson Miller
 * @date 2021-11-05
 * @copyright (c) 2021 Jackson Miller
 */

#include "../util.h"
#include "../elements/ItemSelectionDialog.h"

#include "TargetModel.h"

namespace ui {

TargetModel::TargetModel(std::shared_ptr<data::Library> db, plan::Subfactory &subfactory, QObject *parent) :
    db_(std::move(db)),
    ItemViewModel(subfactory, parent) {
    assert(db_);
}

QVariant TargetModel::data(const QModelIndex &index, int role) const {
    const auto target = subfactory_.product_targets_.at(index.row());
    const auto column = static_cast<Column> (index.column());

    if (role == Qt::ItemDataRole::DisplayRole) {
        if (column == Column::kItem) {
            return QString::fromStdString(target.name());

        } else if (column == Column::kRate) {
            return QString::number(target.rate());

        }

    } else if (role == Qt::ItemDataRole::DecorationRole) {
        if (column == Column::kItem) {
            return util::itemIconFromDisplayName(QString::fromStdString(target.name()));

        }
    }

    return {};
}

bool TargetModel::insertRows(int startRow, int count, const QModelIndex &parent) {
    beginInsertRows(parent, startRow, startRow + count - 1);
//    subfactory_.product_targets_.reserve(subfactory_.product_targets_.size() + count);

    for (int row = startRow; row < startRow + count; ++row) {
        auto *dialog = new ItemSelectionDialog(db_);
        if (dialog->exec() == QDialog::Accepted) {
            data::Item new_target = dialog->getSelectedItem();
            new_target.setRate(static_cast<float> (dialog->getAmount()));

            // Check that this isn't a duplicate target
            // TODO: This still adds a blank row to the table.  Make it not do that.
            bool duplicate = false;
            for (auto &existing_item : subfactory_.product_targets_) {
                if (new_target == existing_item) {
                    existing_item.setRate(existing_item.rate() + new_target.rate());
                    duplicate = true;
                }
            }

            if (!duplicate) {
                subfactory_.product_targets_.emplace(subfactory_.product_targets_.cbegin() + row,
                                                     new_target);
            }
        }
        dialog->deleteLater();
    }

    endInsertRows();
    return true;
}

bool TargetModel::removeRows(int startRow, int count, const QModelIndex &parent) {
    if (count == 0 || subfactory_.product_targets_.size() <= 1) {
        return false;
    }

    const int endRow = startRow + count - 1;
    beginRemoveRows(parent, startRow, endRow);
    subfactory_.product_targets_.erase(subfactory_.product_targets_.begin() + startRow,
                                       subfactory_.product_targets_.begin() + (endRow + 1));
    endRemoveRows();

    return true;
}

void TargetModel::editRow(const QModelIndex &index) {
    auto* dialog = new ItemSelectionDialog(db_);
    dialog->setFromItem(subfactory_.product_targets_.at(index.row()),
                        subfactory_.product_targets_.at(index.row()).rate());

    if (dialog->exec() == QDialog::Accepted) {
        subfactory_.product_targets_.at(index.row()) = dialog->getSelectedItem();
        subfactory_.product_targets_.at(index.row()).setRate(static_cast<float> (dialog->getAmount()));
    }

    dialog->deleteLater();
}

data::Item& TargetModel::getTarget(const QModelIndex &index) const {
    return subfactory_.product_targets_.at(index.row());
}

}