/**
 * Created by jackm on 10/2/2021
 */
 
#include <utility>

#include "plan/ProductLine.h"

namespace plan {

/**
 *
 * @param target
 * @param recipe
 * @param target_per_min
 */
ProductLine::ProductLine(data::Item target,const data::Recipe &recipe, const float &target_per_min) :
		target_(std::move(target)),
		target_per_min_(target_per_min) {
	changeRecipe(recipe);
}

/**
 *
 * @param recipe
 */
void ProductLine::changeRecipe(const data::Recipe &recipe) {
	recipe_ = recipe;
	
	// Match target count with recipe product count
	for (const auto &product : recipe_.productList()) {
		if (product == target_) {
			target_.setAmount(product.amount());
		}
	}
	
	// Update the numbers
	updateMultiplier(target_per_min_);
}

/**
 *
 * @param target_per_min
 */
void ProductLine::updateMultiplier(const float &target_per_min) {
	multiplier_ = target_per_min / (target_.amount() * (60 / recipe_.time()));
}

} // namespace plan