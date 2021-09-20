/**
 * @file ItemButton.h
 * Created by jackm on 9/18/2021
 */

#ifndef SATISFACTORY_PLANNER_ITEMBUTTON_H
#define SATISFACTORY_PLANNER_ITEMBUTTON_H

#include <QPushButton>
#include <QIcon>
#include <QVBoxLayout>
#include <QLabel>

#include "BasicItemButton.h"
#include "ItemButtonLabel.h"

namespace ui {

class ItemButton : public BasicItemButton {
  Q_OBJECT
  
  public:
	ItemButton(QString display_name, const int &item_count, std::shared_ptr<QJsonArray> &db, QWidget* parent = nullptr);
	
	void setItemCount(const int &count);
	
  private:
	QVBoxLayout* layout_ = nullptr;
	ItemButtonLabel* item_count_label_ = nullptr;
	int item_count_;
	
	std::shared_ptr<QJsonArray> db_;
	
	QString formatItemNumber(const int &num);
};

} // namespace ui

#endif //SATISFACTORY_PLANNER_ITEMBUTTON_H
