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

SubfactoryPane::SubfactoryPane(std::shared_ptr<plan::Factory> factory, std::shared_ptr<data::Library> db, QWidget *parent) :
    factory_(std::move(factory)),
    db_(std::move(db)),
    QWidget(parent) {

    layout_ = new QVBoxLayout(this);
    InitToolbar();

    subfactory_list_ = new QListView(this);
    subfactory_model_ = new SubfactoryListModel(factory_, this);
    subfactory_list_->setModel(subfactory_model_);
    connect(subfactory_list_->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &SubfactoryPane::SSubfactoryChanged);

    layout_->addWidget(subfactory_list_);

    if (factory_->subfactories_.empty()) {
        SAddSubfactory();
    }

}

void SubfactoryPane::InitToolbar() {
	toolbar_ = new QToolBar(this);
    toolbar_->setIconSize(QSize(45, 45));
	
	// WindowActions
    actions_.act_add = new QAction("+", this);
    actions_.act_add->setToolTip(tr("Add New"));
	toolbar_->addAction(actions_.act_add);
    connect(actions_.act_add, &QAction::triggered, this, &SubfactoryPane::SAddSubfactory);

    actions_.act_edit = new QAction("i", this);
    actions_.act_edit->setToolTip(tr("Edit"));
	toolbar_->addAction(actions_.act_edit);
    connect(actions_.act_edit, &QAction::triggered, this, &SubfactoryPane::SEditSubfactory);

    actions_.act_delete = new QAction("-", this);
    actions_.act_delete->setToolTip(tr("Delete"));
	toolbar_->addAction(actions_.act_delete);
    connect(actions_.act_delete, &QAction::triggered, this, &SubfactoryPane::SRemoveSubfactory);

    layout_->addWidget(toolbar_);
}

plan::Subfactory& SubfactoryPane::selectedSubfactory() {
    return subfactory_model_->getSubfactory(subfactory_list_->selectionModel()->currentIndex());
}

void SubfactoryPane::SAddSubfactory() {
    subfactory_model_->insertRows(subfactory_model_->rowCount(QModelIndex()), 1, QModelIndex());

    const unsigned int row = subfactory_model_->rowCount(QModelIndex()) - 1;
    const plan::Subfactory &subfactory = factory_->subfactories_.at(row);

    auto* dialog = new SubfactoryEditDialog(subfactory, this);
    if (dialog->exec() == SubfactoryEditDialog::Accepted) {
        QString subfactory_name = dialog->getName();
        if (subfactory_name.isEmpty()) {
            factory_->subfactories_.at(row).setLabel("untitled");
        } else {
            factory_->subfactories_.at(row).setLabel(dialog->getName().toStdString());
        }

        factory_->subfactories_.at(row).setIcon(dialog->getIcon().toStdString());
    }
    dialog->deleteLater();
}

void SubfactoryPane::SEditSubfactory() {
    const QModelIndex selection = subfactory_list_->selectionModel()->currentIndex();
    if (!selection.isValid()) {
        return;
    }
    const unsigned int row = selection.row();
    const plan::Subfactory &subfactory = factory_->subfactories_.at(row);

    auto* dialog = new SubfactoryEditDialog(subfactory, this);
    if (dialog->exec() == SubfactoryEditDialog::Accepted) {
        factory_->subfactories_.at(row).setLabel(dialog->getName().toStdString());
        factory_->subfactories_.at(row).setIcon(dialog->getIcon().toStdString());
    }
    dialog->deleteLater();
}

void SubfactoryPane::SRemoveSubfactory() {
    // Check that we're not removing the only subfactory
    if (factory_->subfactories_.size() <= 1) {
        return;
    }

    const auto row = subfactory_list_->selectionModel()->currentIndex().row();

    const QString &subfac_name = subfactory_model_->data(
            subfactory_list_->selectionModel()->currentIndex(),
            Qt::DisplayRole
            ).toString();

    QString delete_message = tr("Are you sure you want to delete the subfactory '%1'?").arg(subfac_name);

    const auto confirm_delete = QMessageBox::question(this, tr("Delete Subfactory"), delete_message);
    if (confirm_delete == QMessageBox::Yes) {
        subfactory_model_->removeRows(row, 1, QModelIndex());
    }
}

} // namespace ui