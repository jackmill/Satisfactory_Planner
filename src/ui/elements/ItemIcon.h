/**
 * @project Satisfactory_Planner
 * @file ItemIcon.h
 *
 * @author Jackson Miller
 * @date 2021-09-18
 * @copyright (c) 2021 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_ITEMICON_H
#define SATISFACTORY_PLANNER_ITEMICON_H

#include <QPushButton>
#include <QIcon>
#include <QVBoxLayout>
#include <QLabel>

#include "data/Library.h"

namespace ui {

class ItemIcon : public QPushButton {
  
  public:
	explicit ItemIcon(data::Item &item, QWidget* parent = nullptr);

	void updateItemCount(const int &count);
    void setLabelCount(const int count);
    void setCleared();
	
  private:
	QVBoxLayout* layout_ = nullptr;
	QLabel* item_count_label_ = nullptr;

  protected:
	data::Item& btn_item_;
};

} // namespace ui

#endif //SATISFACTORY_PLANNER_ITEMICON_H
