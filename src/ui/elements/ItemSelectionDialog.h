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
	explicit ItemSelectionDialog(data::Library* db, QWidget* parent = nullptr);
    ItemSelectionDialog(const data::Item& item, data::Library* db, QWidget* parent = nullptr);

    void setFromItem(const data::Item &item);
    void setFromItem(const data::Item &item, float rate);

    data::Item getSelectedItem();
    int getDialogRate() { return dialog_rate_->value(); };
    bool hasRate() { return dialog_rate_->value() > 0; };
	void allowItemChange(bool allow_item_change);

  private:
    data::Library* db_;

    ItemListModel* model_ = nullptr;

    QComboBox* dialog_item_ = nullptr;
    QSpinBox* dialog_rate_ = nullptr;

	QDialogButtonBox* actions_ = nullptr;
	QVBoxLayout* layout_ = nullptr;

  private slots:
    void checkDialogRate();
};

} // namespace ui

#endif //SATISFACTORY_PLANNER_ITEMSELECTIONDIALOG_H
