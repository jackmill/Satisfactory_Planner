/**
 * @project Satisfactory_Planner
 * @file ItemButton.cpp
 *
 * @author Jackson Miller
 * @date 2021-10-05
 * @copyright (c) 2021 Jackson Miller
 */

#include "ItemButton.h"
#include "ItemSelectionDialog.h"
#include "../util.h"

namespace ui {

ItemButton::ItemButton(data::Item &item, std::shared_ptr<data::Library> db, QWidget *parent) :
    db_(std::move(db)),
    ItemIcon(item, parent) {

    connect(this, &ItemIcon::clicked, this, [&]() { selectItem(btn_item_); });
}

void ItemButton::selectItem(const data::Item &item) {
    auto* dialog = new ItemSelectionDialog(db_, this);
    dialog->setFromItem(item);

    if (dialog->exec() == QDialog::Accepted) {
        btn_item_ = dialog->getSelectedItem();
        updateItemCount(dialog->getAmount());
        setIcon(util::itemIconFromDisplayName(QString::fromStdString(btn_item_.name())));
    }
    dialog->deleteLater();
}

}