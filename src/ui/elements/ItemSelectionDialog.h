/**
 * @project Satisfactory_Planner
 * @file ItemSelectionDialog.h
 *
 * @author Jackson Miller
 * @date 2021-09-19
 * @copyright (c) 2021 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_ITEMSELECTIONDIALOG_H
#define SATISFACTORY_PLANNER_ITEMSELECTIONDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QComboBox>
#include <QSpinBox>

#include "data/Library.h"
#include "ItemListModel.h"

namespace ui {

class ItemSelectionDialog : public QDialog {
  public:
	explicit ItemSelectionDialog(std::shared_ptr<data::Library> db, QWidget* parent = nullptr);

    void setFromItem(const data::Item &item);
    void setFromItem(const data::Item &item, float rate);

    data::Item getSelectedItem();
    int getAmount() { return amount_->value(); };
    bool hasAmount() { return amount_->value() > 0; };
	
  private:
    std::shared_ptr<data::Library> db_;
    ItemListModel* model_ = nullptr;

    QComboBox* item_ = nullptr;
    QSpinBox* amount_ = nullptr;

	QDialogButtonBox* actions_ = nullptr;
	QVBoxLayout* layout_ = nullptr;

  private slots:
    void checkAmount();
};

} // namespace ui

#endif //SATISFACTORY_PLANNER_ITEMSELECTIONDIALOG_H
