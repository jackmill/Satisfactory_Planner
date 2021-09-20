/**
 * @file ItemSelectionDialog.h
 * Created by jackm on 9/19/2021
 */

#ifndef SATISFACTORY_PLANNER_ITEMSELECTIONDIALOG_H
#define SATISFACTORY_PLANNER_ITEMSELECTIONDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QLineEdit>

namespace ui {

class ItemSelectionDialog : public QDialog {
  public:
	ItemSelectionDialog(QWidget* parent = nullptr);
	
  private:
	QDialogButtonBox* actions_ = nullptr;
	QVBoxLayout* layout_ = nullptr;
};

} // namespace ui

#endif //SATISFACTORY_PLANNER_ITEMSELECTIONDIALOG_H
