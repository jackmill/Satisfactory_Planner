/**
 * @project Satisfactory_Planner
 * @file ProductLine.h
 *
 * @author Jackson Miller
 * @date 2021-10-02
 * @copyright (c) 2021 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_PRODUCTLINE_H
#define SATISFACTORY_PLANNER_PRODUCTLINE_H

#include <vector>

#include "data/Recipe.h"

namespace plan {

class ProductLine {
  public:
	ProductLine(data::Item target,data::Recipe recipe, const float &target_per_min);
	
	void changeRecipe(const data::Recipe &recipe);
	void updateMultiplier(const float &target_per_min);
	
	[[nodiscard]] float targetOutput() const { return target_per_min_; };
	[[nodiscard]] float multiplier() const { return multiplier_; };
	data::Recipe recipe() { return recipe_; };

    [[nodiscard]] float calcPower() const;
    [[nodiscard]] std::vector<data::Item> calcIngredients() const;
    [[nodiscard]] std::vector<data::Item> calcProducts() const;

    void setDone(bool done) { complete_ = done; };

  private:
	data::Item target_;
	float target_per_min_;
	data::Recipe recipe_;
	float multiplier_;

    bool complete_ = false;
};

} // namespace plan


#endif //SATISFACTORY_PLANNER_PRODUCTLINE_H
