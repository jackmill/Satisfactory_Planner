/**
 * @project Satisfactory_Planner
 * @file SubfactoryEditDialog.cpp
 * 
 * @author Jackson Miller
 * @date 2021-10-06
 * @copyright (c) 2021 Jackson Miller
 */

#include <QLabel>

#include "SubfactoryEditDialog.h"

namespace ui {

SubfactoryEditDialog::SubfactoryEditDialog(const plan::Subfactory &subfactory, QWidget *parent) :
    QDialog(parent) {
    setWindowTitle("Edit Subfactory");

    layout_ = new QFormLayout(this);

    name_ = new QLineEdit(this);
    if (!subfactory.label().empty()) {
        name_->setText(QString::fromStdString(subfactory.label()));
    }

    icon_ = new QLineEdit(this);
    if (!subfactory.icon().empty()) {
        icon_->setText(QString::fromStdString(subfactory.icon()));
    }

    actions_ = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(actions_, &QDialogButtonBox::accepted, this, &SubfactoryEditDialog::accept);
    connect(actions_, &QDialogButtonBox::rejected, this, &SubfactoryEditDialog::reject);

    layout_->addRow(tr("Label: "), name_);
    layout_->addRow(tr("Icon: "), icon_);
    layout_->addWidget(actions_);
}

}