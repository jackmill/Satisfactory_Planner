/**
 * @project Satisfactory_Planner
 * @file ItemButton.cpp
 *
 * @author Jackson Miller
 * @date 2021-10-05
 * @copyright (c) 2021 Jackson Miller
 */

#include <QMenu>

#include "ItemButton.h"
#include "ItemSelectionDialog.h"
#include "../util.h"

namespace ui {

ItemButton::ItemButton(data::Item &item, std::shared_ptr<data::Library> db, QWidget *parent) :
    db_(std::move(db)),
    ItemIcon(item, parent) {

    initMenu();
}

void ItemButton::initMenu() {
    // Add to table
    actions_.act_add_to_table = new QAction(tr("Add to Table"), this);

    // Edit Item
    actions_.act_edit = new QAction(tr("Edit Item"), this);
    connect(actions_.act_edit, &QAction::triggered, this, [&]() { editItem(btn_item_); });

    // Delete Item
    actions_.act_delete = new QAction(tr("Delete Item"), this);

    // Init Menu
    auto* menu = new QMenu(this);
    menu->addAction(actions_.act_add_to_table);
    menu->addSeparator();
    menu->addAction(actions_.act_edit);
    menu->addAction(actions_.act_delete);

    setMenu(menu);
}

void ItemButton::editItem(const data::Item &item) {
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