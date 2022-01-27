/**
 * @project Satisfactory_Planner
 * @file ClockSpeedEditDialog.cpp
 * 
 * @author Jackson Miller
 * @date 2022-01-26
 * @copyright (c) 2022 Jackson Miller
 */

#include <QPushButton>

#include "ClockSpeedEditDialog.h"

namespace ui {

ClockSpeedEditDialog::ClockSpeedEditDialog(plan::ProductLine& product_line, QWidget* parent) :
	QDialog(parent),
	line_(&product_line),
	k_base_machines_((line_->clock() / 100) * line_->multiplier()) {

	/**
	 * C - Clock Speed
	 * Nm - Number of machines with a clock speed of 100%
	 * Nc - Number of machines with clock speed set
	 *
	 * C = Nm / Nc
	 * Nm = C * Nc
	 * Nc = Nm / C
	 */

	setWindowTitle(tr("Adjust Clock Speed"));

	clock_speed_ = new QDoubleSpinBox(this);
	clock_speed_->setMinimum(0.01);
	clock_speed_->setMaximum(250);
	clock_speed_->setValue(line_->clock());
	connect(clock_speed_,
	        QOverload<double>::of(&QDoubleSpinBox::valueChanged),
	        this,
			&ClockSpeedEditDialog::S_clockSpeedChanged);

	num_machines_ = new QDoubleSpinBox(this);
	num_machines_->setMinimum(k_base_machines_ / 2.5); // number of machines at clock 250%
	num_machines_->setMaximum(10000);
	num_machines_->setValue(line_->multiplier());
	connect(num_machines_,
	        QOverload<double>::of(&QDoubleSpinBox::valueChanged),
	        this,
			&ClockSpeedEditDialog::S_numMachinesChanged);

	actions_ = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::RestoreDefaults, this);
	connect(actions_, &QDialogButtonBox::accepted, this, &ClockSpeedEditDialog::accept);
	connect(actions_, &QDialogButtonBox::rejected, this, &ClockSpeedEditDialog::reject);
	connect(actions_->button(QDialogButtonBox::RestoreDefaults),
			&QPushButton::clicked,
			[this]{ clock_speed_->setValue(100); });

	layout_ = new QFormLayout(this);
	layout_->addRow(tr("&Clock Speed: "), clock_speed_);
	layout_->addRow(tr("&Machines: "), num_machines_);
	layout_->addWidget(actions_);

}

void ClockSpeedEditDialog::S_clockSpeedChanged() {
	if (!editing_begun_) {
		editing_begun_ = true;

		num_machines_->setValue(k_base_machines_ / (clock_speed_->value() / 100));

		editing_begun_ = false;
	}
}

void ClockSpeedEditDialog::S_numMachinesChanged() {
	if (!editing_begun_) {
		editing_begun_ = true;

		clock_speed_->setValue((k_base_machines_ / num_machines_->value()) * 100);

		editing_begun_ = false;
	}
}

}