/**
 * @project Satisfactory_Planner
 * @file PercentEditDialog.cpp
 * 
 * @author Jackson Miller
 * @date 2022-01-26
 * @copyright (c) 2022 Jackson Miller
 */

#include <QPushButton>
#include <QVBoxLayout>

#include "PercentEditDialog.h"

namespace ui {

PercentEditDialog::PercentEditDialog(plan::ProductLine& product_line, QWidget* parent) :
		QDialog(parent),
		line_(&product_line),
		k_max_percent_((100 - line_->target()->completion()) + line_->percent()),
		k_max_machines_(line_->multiplier() * (k_max_percent_ / line_->percent())){

	setWindowTitle(tr("Edit Line Percentage"));

	percent_target_ = new QDoubleSpinBox(this);
	percent_target_->setMinimum(0.01);
	percent_target_->setMaximum(k_max_percent_);
	percent_target_->setValue(line_->percent());
	connect(percent_target_,
	        QOverload<double>::of(&QDoubleSpinBox::valueChanged),
			this,
			&PercentEditDialog::S_percentTargetChanged);

	item_output_target_ = new QDoubleSpinBox(this);
	item_output_target_->setMinimum(0.01);
	item_output_target_->setMaximum(line_->target()->rate() * (k_max_percent_ / 100));
	item_output_target_->setValue(line_->productOutput());
	connect(item_output_target_,
	        QOverload<double>::of(&QDoubleSpinBox::valueChanged),
	        this,
	        &PercentEditDialog::S_outputTargetChanged);

	num_machines_target_ = new QDoubleSpinBox(this);
	num_machines_target_->setMinimum(0.01);
	num_machines_target_->setMaximum(k_max_machines_);
	num_machines_target_->setValue(line_->multiplier());
	connect(num_machines_target_,
	        QOverload<double>::of(&QDoubleSpinBox::valueChanged),
	        this,
	        &PercentEditDialog::S_machinesTargetChanged);

	actions_ = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::RestoreDefaults, this);
	connect(actions_, &QDialogButtonBox::accepted, this, &PercentEditDialog::accept);
	connect(actions_, &QDialogButtonBox::rejected, this, &PercentEditDialog::reject);
	connect(actions_->button(QDialogButtonBox::RestoreDefaults),
			&QPushButton::clicked,
			[this]{ percent_target_->setValue(100); });

	layout_ = new QFormLayout(this);
	layout_->addRow(tr("&Percent: "), percent_target_);
	layout_->addRow(tr("&Output Rate: "), item_output_target_);
	layout_->addRow(tr("&Machines: "), num_machines_target_);
	layout_->addWidget(actions_);
}

void PercentEditDialog::S_percentTargetChanged() {
	if (!editing_begun_) {
		editing_begun_ = true;
		const auto new_percent = percent_target_->value() / 100;

		item_output_target_->setValue(line_->target()->rate() * new_percent);
		num_machines_target_->setValue(k_max_machines_ * new_percent);

		editing_begun_ = false;
	}
}

void PercentEditDialog::S_outputTargetChanged() {
	if (!editing_begun_) {
		editing_begun_ = true;
		const auto new_percent = (item_output_target_->value() / line_->targetOutput());

		percent_target_->setValue(new_percent * 100);
		num_machines_target_->setValue(k_max_machines_ * new_percent);
		editing_begun_ = false;
	}
}

void PercentEditDialog::S_machinesTargetChanged() {
	if (!editing_begun_) {
		editing_begun_ = true;
		const auto new_percent = (num_machines_target_->value() / line_->multiplier()) * (line_->percent() / k_max_percent_);

		percent_target_->setValue(new_percent * 100);
		item_output_target_->setValue(line_->target()->rate() * new_percent);
		editing_begun_ = false;
	}
}

}