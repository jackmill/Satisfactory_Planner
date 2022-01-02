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

    icon_ = new QComboBox(this);
	icon_model_ = new IconListModel(this);
    icon_->setModel(icon_model_);
	icon_->setIconSize(QSize(40, 40));
	if (!subfactory.icon().empty()) {
		QString icon_filename = QString::fromStdString(subfactory.icon());
		icon_->setCurrentIndex(icon_model_->findIconIndex(icon_filename));
	}

    actions_ = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(actions_, &QDialogButtonBox::accepted, this, &SubfactoryEditDialog::accept);
    connect(actions_, &QDialogButtonBox::rejected, this, &SubfactoryEditDialog::reject);

    layout_->addRow(tr("Label: "), name_);
    layout_->addRow(tr("Icon: "), icon_);
    layout_->addWidget(actions_);
}

QString SubfactoryEditDialog::getIcon() const {
	return icon_model_->getIconString(icon_->currentIndex());
}


}