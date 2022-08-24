/**
 * @project Satisfactory_Planner
 * @file SubfactoryPane.cpp
 *
 * @author Jackson Miller
 * @date 2021-09-17
 * @copyright (c) 2021 Jackson Miller
 */

#include <QMessageBox>

#include "SubfactoryPane.h"
#include "SubfactoryEditDialog.h"

namespace ui {

SubfactoryPane::SubfactoryPane(plan::Factory* factory, data::Library* db, QWidget *parent) :
    factory_(factory),
    db_(db),
    QWidget(parent) {

    layout_ = new QVBoxLayout(this);
    InitToolbar();

    subfactory_list_ = new QListView(this);
    subfactory_model_ = new SubfactoryListModel(factory_, this);
    subfactory_list_->setModel(subfactory_model_);

    connect(subfactory_list_->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &SubfactoryPane::S_selectedSubfactoryChanged);

    layout_->addWidget(subfactory_list_);

    if (factory_->subfactories_.empty()) {
        plan::Subfactory new_subfactory("untitled", "");

        subfactory_model_->insertRow(subfactory_model_->rowCount(QModelIndex()), QModelIndex(),
                                     new_subfactory);
    }

    connect(subfactory_model_, &SubfactoryListModel::dataChanged, this, &SubfactoryPane::S_factoryChanged);
    connect(subfactory_model_, &SubfactoryListModel::rowsInserted, this, &SubfactoryPane::S_factoryChanged);
    connect(subfactory_model_, &SubfactoryListModel::rowsRemoved, this, &SubfactoryPane::S_factoryChanged);
}

void SubfactoryPane::InitToolbar() {
	toolbar_ = new QToolBar(this);
    toolbar_->setIconSize(QSize(45, 45));
	
	// WindowActions
    actions_.act_add = new QAction("+", this);
    actions_.act_add->setToolTip(tr("Add New"));
	toolbar_->addAction(actions_.act_add);
    connect(actions_.act_add, &QAction::triggered, this, &SubfactoryPane::S_AddSubfactory);

    actions_.act_edit = new QAction("i", this);
    actions_.act_edit->setToolTip(tr("Edit"));
	toolbar_->addAction(actions_.act_edit);
    connect(actions_.act_edit, &QAction::triggered, this, &SubfactoryPane::S_EditSubfactory);

    actions_.act_delete = new QAction("-", this);
    actions_.act_delete->setToolTip(tr("Delete"));
	toolbar_->addAction(actions_.act_delete);
    connect(actions_.act_delete, &QAction::triggered, this, &SubfactoryPane::S_RemoveSubfactory);

    layout_->addWidget(toolbar_);
}

plan::Subfactory* SubfactoryPane::selectedSubfactory() {
    return factory_->subfactories_.at(subfactory_list_->selectionModel()->currentIndex().row()).get();
}

void SubfactoryPane::S_AddSubfactory() {
    auto new_subfactory = plan::Subfactory();

    auto* dialog = new SubfactoryEditDialog(new_subfactory, this);
    if (dialog->exec() == SubfactoryEditDialog::Accepted) {
        QString subfactory_name = dialog->getName();
        if (subfactory_name.isEmpty()) {
            new_subfactory.setLabel("untitled");
        } else {
            new_subfactory.setLabel(dialog->getName().toStdString());
        }

        new_subfactory.setIcon(dialog->getIcon().toStdString());

        subfactory_model_->insertRow(subfactory_model_->rowCount(QModelIndex()), QModelIndex(),
                                     new_subfactory);
    }
    dialog->deleteLater();
}

void SubfactoryPane::S_EditSubfactory() {
    const QModelIndex selection = subfactory_list_->selectionModel()->currentIndex();
    if (!selection.isValid()) {
        return;
    }
    const int row = selection.row();
    plan::Subfactory* subfactory = factory_->subfactoryAt(row);

    auto* dialog = new SubfactoryEditDialog(*subfactory, this);
    if (dialog->exec() == SubfactoryEditDialog::Accepted) {
        subfactory->setLabel(dialog->getName().toStdString());
        subfactory->setIcon(dialog->getIcon().toStdString());
    }
    dialog->deleteLater();
}

void SubfactoryPane::S_RemoveSubfactory() {
    // Check that we're not removing the only subfactory
    if (factory_->numSubfactories() <= 1) {
        return;
    }

    const auto row = subfactory_list_->selectionModel()->currentIndex().row();

    const QString &subfactory_name = subfactory_model_->data(
            subfactory_list_->selectionModel()->currentIndex(),
            Qt::DisplayRole
            ).toString();

    QString delete_message = tr("Are you sure you want to delete the subfactory '%1'?").arg(subfactory_name);

    const auto confirm_delete = QMessageBox::question(this, tr("Delete Subfactory"), delete_message);
    if (confirm_delete == QMessageBox::Yes) {
        subfactory_model_->removeRows(row, 1, QModelIndex());
    }
}

} // namespace ui