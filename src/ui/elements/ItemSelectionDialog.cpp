/**
 * @project Satisfactory_Planner
 * @file ItemSelectionDialog.cpp
 *
 * @author Jackson Miller
 * @date 2021-09-19
 * @copyright (c) 2021 Jackson Miller
 */

#include <QPushButton>

#include "ItemSelectionDialog.h"

namespace ui {

ItemSelectionDialog::ItemSelectionDialog(std::shared_ptr<data::Library> db, QWidget *parent) :
		db_(std::move(db)),
        QDialog(parent) {
	
	layout_ = new QVBoxLayout(this);
    model_ = new ItemListModel(db_, this);

    item_ = new QComboBox(this);
    item_->setModel(model_);

    amount_ = new QSpinBox(this);
    amount_->setMinimum(0);
    amount_->setMaximum(100000 - 1);

    actions_ = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(actions_, &QDialogButtonBox::accepted, this, &ItemSelectionDialog::accept);
    connect(actions_, &QDialogButtonBox::rejected, this, &ItemSelectionDialog::reject);

    layout_->addWidget(item_);
    layout_->addWidget(amount_);
    layout_->addWidget(actions_);
}

void ItemSelectionDialog::setFromItem(const data::Item &item) {
    int item_index;
    for (auto db_item = db_->getItemsSorted().cbegin(); db_item != db_->getItemsSorted().cend(); ++db_item) {
        if (item == *db_item) {
            item_index = static_cast<int>(db_item - db_->getItemsSorted().cbegin());
        }
    }

    item_->setCurrentIndex(item_index);
    amount_->setValue(item.amount());
}

data::Item ItemSelectionDialog::getSelectedItem() {
    return model_->itemAtRow(item_->currentIndex());
}

}