/**
 * @project Satisfactory_Planner
 * @file ClockSpeedEditDialog.h
 * 
 * @author Jackson Miller
 * @date 2022-01-26
 * @copyright (c) 2022 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_CLOCKSPEEDEDITDIALOG_H
#define SATISFACTORY_PLANNER_CLOCKSPEEDEDITDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QDoubleSpinBox>
#include <QFormLayout>

#include "plan/Subfactory.h"

namespace ui {

class ClockSpeedEditDialog final : public QDialog {
	Q_OBJECT
  public:
	explicit ClockSpeedEditDialog(plan::ProductLine& product_line, QWidget* parent = nullptr);

	[[nodiscard]] float getNewMult() const { return static_cast<float> (clock_speed_->value()); };

  private:
	plan::ProductLine* line_;

	QFormLayout* layout_ = nullptr;
	QDialogButtonBox* actions_ = nullptr;

	QDoubleSpinBox* clock_speed_ = nullptr;
	QDoubleSpinBox* num_machines_ = nullptr;

	bool editing_begun_ = false;
	const float k_base_machines_;



  private Q_SLOTS:
	void S_clockSpeedChanged();
    void S_numMachinesChanged();
};

}

#endif //SATISFACTORY_PLANNER_CLOCKSPEEDEDITDIALOG_H
