/**
 * @project Satisfactory_Planner
 * @file ProductLine.cpp
 *
 * @author Jackson Miller
 * @date 2021-10-02
 * @copyright (c) 2021 Jackson Miller
 */
 
#include <utility>
#include <cmath>

#include "plan/ProductLine.h"

namespace plan {

ProductLine::ProductLine(data::Item target,data::Recipe recipe, const float &target_per_min) :
		target_(std::move(target)),
        recipe_(std::move(recipe)),
		target_per_min_(target_per_min) {
    changeRecipe(recipe);
}

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

void ProductLine::updateMultiplier(const float &target_per_min) {
	multiplier_ = target_per_min / (target_.amount() * (60 / recipe_.time()));
}

float ProductLine::calcPower() const {
    return multiplier_ * static_cast<float>(recipe_.machine().power());
}

std::vector<data::Item> ProductLine::calcIngredients() const {
    std::vector<data::Item> out = recipe_.ingredientList();
    for (auto &item : out) {
        item.setAmount(static_cast<int>(std::round(multiplier_ * static_cast<float>(item.amount()))));
    }
    return out;
}

std::vector<data::Item> ProductLine::calcProducts() const {
    std::vector<data::Item> out = recipe_.productList();
    for (auto &item : out) {
        item.setAmount(static_cast<int>(std::round(multiplier_ * static_cast<float>(item.amount()))));
    }
    return out;
}

} // namespace plan