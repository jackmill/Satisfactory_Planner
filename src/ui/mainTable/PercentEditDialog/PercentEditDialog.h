/**
 * @project Satisfactory_Planner
 * @file PercentEditDialog.h
 * 
 * @author Jackson Miller
 * @date 2022-01-26
 * @copyright (c) 2022 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_PERCENTEDITDIALOG_H
#define SATISFACTORY_PLANNER_PERCENTEDITDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QModelIndex>

#include "plan/Subfactory.h"

namespace ui {

class PercentEditDialog final: public QDialog {
	Q_OBJECT
  public:
	explicit PercentEditDialog(plan::ProductLine* product_line, QWidget* parent = nullptr);

	[[nodiscard]] float selectedPercent() const { return static_cast<float> (percent_target_->value()); };

  private:
	plan::ProductLine* line_;

	QFormLayout* layout_ = nullptr;
	QDialogButtonBox* actions_ = nullptr;

	QDoubleSpinBox* percent_target_ = nullptr;
	QDoubleSpinBox* item_output_target_ = nullptr;
	QDoubleSpinBox* num_machines_target_ = nullptr;

	const float k_max_percent_;
	const float k_max_machines_;
	bool editing_begun_ = false;


  private Q_SLOTS:
	void S_percentTargetChanged();
    void S_outputTargetChanged();
	void S_machinesTargetChanged();

};

}

#endif //SATISFACTORY_PLANNER_PERCENTEDITDIALOG_H
