/**
 * @project Satisfactory_Planner
 * @file RecipeIconList.h
 * 
 * @author Jackson Miller
 * @date 2022-01-10
 * @copyright (c) 2022 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_RECIPEICONLIST_H
#define SATISFACTORY_PLANNER_RECIPEICONLIST_H

#include <QWidget>
#include <QHBoxLayout>

#include "../../elements/TableIcon.h"
#include "data/Item.h"

namespace ui {

class RecipeIconList : public QWidget {
  public:
	explicit RecipeIconList(const std::vector<data::Item>& item_list, QWidget* parent = nullptr);

	static const int kPadding = 2;

  private:
	QHBoxLayout* layout_ = nullptr;
};

} // namespace ui

#endif //SATISFACTORY_PLANNER_RECIPEICONLIST_H
