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

ItemSelectionDialog::ItemSelectionDialog(std::shared_ptr<data::Library> db, QWidget* parent) :
		db_(std::move(db)),
        QDialog(parent) {
	
	layout_ = new QVBoxLayout(this);
    model_ = new ItemListModel(db_, this);

    dialog_item_ = new QComboBox(this);
    dialog_item_->setModel(model_);
	dialog_item_->setIconSize(QSize(40, 40));

    dialog_rate_ = new QSpinBox(this);
    dialog_rate_->setMinimum(0);
    dialog_rate_->setMaximum(100000 - 1);

    actions_ = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(actions_, &QDialogButtonBox::accepted, this, &ItemSelectionDialog::accept);
    connect(actions_, &QDialogButtonBox::rejected, this, &ItemSelectionDialog::reject);
    checkDialogRate();
    connect(dialog_rate_, &QSpinBox::textChanged, this, &ItemSelectionDialog::checkDialogRate);

    layout_->addWidget(dialog_item_);
    layout_->addWidget(dialog_rate_);
    layout_->addWidget(actions_);
}

ItemSelectionDialog::ItemSelectionDialog(const data::Item& item, std::shared_ptr<data::Library> db, QWidget* parent) :
		ItemSelectionDialog(std::move(db), parent) {
    setFromItem(item);
}

void ItemSelectionDialog::setFromItem(const data::Item &item) {
    int item_index;
    for (auto db_item = db_->getItemsSorted().cbegin(); db_item != db_->getItemsSorted().cend(); ++db_item) {
        if (item == *db_item) {
            item_index = static_cast<int>(db_item - db_->getItemsSorted().cbegin());
        }
    }

    dialog_item_->setCurrentIndex(item_index);
    dialog_rate_->setValue(static_cast<int> (item.rate()));
}

void ItemSelectionDialog::setFromItem(const data::Item &item, float rate) {
    int item_index;
    for (auto db_item = db_->getItemsSorted().cbegin(); db_item != db_->getItemsSorted().cend(); ++db_item) {
        if (item == *db_item) {
            item_index = static_cast<int>(db_item - db_->getItemsSorted().cbegin());
        }
    }

    dialog_item_->setCurrentIndex(item_index);
    dialog_rate_->setValue(static_cast<int> (rate));
}

data::Item ItemSelectionDialog::getSelectedItem() {
    data::Item selected_item = model_->itemAtRow(dialog_item_->currentIndex());
    selected_item.setRate(static_cast<float> (dialog_rate_->value()));

    return selected_item;
}

void ItemSelectionDialog::allowItemChange(bool allow_item_change) {
	dialog_item_->setEnabled(allow_item_change);
	if (!allow_item_change) {
		dialog_item_->setToolTip(tr("Targets already on the table cannot be changed"));
	}
}

void ItemSelectionDialog::checkDialogRate() {
    actions_->button(QDialogButtonBox::Ok)->setEnabled(hasRate());
}

}