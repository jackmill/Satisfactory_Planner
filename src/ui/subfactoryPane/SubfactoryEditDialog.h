/**
 * @project Satisfactory_Planner
 * @file SubfactoryEditDialog.h
 * 
 * @author Jackson Miller
 * @date 2021-10-06
 * @copyright (c) 2021 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_SUBFACTORYEDITDIALOG_H
#define SATISFACTORY_PLANNER_SUBFACTORYEDITDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QFormLayout>
#include <QDialogButtonBox>

#include "plan/Subfactory.h"

namespace ui {

class SubfactoryEditDialog : public QDialog {
  public:
    SubfactoryEditDialog(const plan::Subfactory &subfactory, QWidget* parent = nullptr);

    [[nodiscard]] QString getName() const { return name_->text(); };
    [[nodiscard]] QString getIcon() const { return icon_->text(); };

  private:
    QLineEdit* name_ = nullptr;
    QLineEdit* icon_ = nullptr;
    QDialogButtonBox* actions_ = nullptr;

    QFormLayout* layout_ = nullptr;

};

}
#endif //SATISFACTORY_PLANNER_SUBFACTORYEDITDIALOG_H
