/**
 * Created by jackm on 10/2/2021
 */

#ifndef SATISFACTORY_PLANNER_PRODUCTLINE_H
#define SATISFACTORY_PLANNER_PRODUCTLINE_H

#include <vector>

#include "data/Recipe.h"

namespace plan {

class ProductLine {
  public:
	ProductLine(data::Item target,const data::Recipe &recipe, const float &target_per_min);
	
	void changeRecipe(const data::Recipe &recipe);
	void updateMultiplier(const float &target_per_min);
	
	float targetOutput() { return target_per_min_; };
	float multiplier() { return multiplier_; };
	data::Recipe recipe() { return recipe_; };
	
  private:
	data::Item target_;
	float target_per_min_;
	data::Recipe recipe_;
	float multiplier_;
};

} // namespace plan


#endif //SATISFACTORY_PLANNER_PRODUCTLINE_H
