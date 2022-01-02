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
	explicit ItemIcon(std::shared_ptr<data::Item> item, QWidget* parent = nullptr);

	void updateItemCount(const float& count);
    void setLabelCount(float count);
    void setCleared();

	constexpr static const QSize kSize_ = QSize(45, 45);
	
  private:
	QVBoxLayout* layout_ = nullptr;
	QLabel* item_count_label_ = nullptr;

  protected:
	std::shared_ptr<data::Item> btn_item_;
};

} // namespace ui

#endif //SATISFACTORY_PLANNER_ITEMICON_H
