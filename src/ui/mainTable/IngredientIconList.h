/**
 * @project Satisfactory_Planner
 * @file IngredientIconList.h
 * 
 * @author Jackson Miller
 * @date 2022-01-10
 * @copyright (c) 2022 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_INGREDIENTICONLIST_H
#define SATISFACTORY_PLANNER_INGREDIENTICONLIST_H

#include <vector>

#include <QWidget>
#include <QHBoxLayout>

#include "data/Item.h"

namespace ui {

class IngredientIconList : public QWidget {
  public:
	explicit IngredientIconList(const std::vector<data::Item>& ingredients_list, QWidget* parent = nullptr);

	static const int kPadding = 2;

  private:
	QHBoxLayout* layout_ = nullptr;
};

} // namespace ui

#endif //SATISFACTORY_PLANNER_INGREDIENTICONLIST_H
