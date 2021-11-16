/**
 * @project Satisfactory_Planner
 * @file ProductLine.cpp
 *
 * @author Jackson Miller
 * @date 2021-10-02
 * @copyright (c) 2021 Jackson Miller
 */

#include <cmath>

#include "plan/ProductLine.h"

namespace plan {

void to_json(nlohmann::json &json, const ProductLine &product_line) {
    json["target"] = product_line.target_;
    json["recipe"] = product_line.recipe_.className();
}

ProductLine::ProductLine(const data::Item& target, const data::Recipe& recipe) :
		target_(target),
        recipe_(recipe),
        multiplier_(1) {
    timing_coefficient_ = static_cast<float> (60.0 / recipe_.time());
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
    timing_coefficient_ = static_cast<float> (60.0 / recipe_.time());
	updateMultiplier(target_.rate());
}

void ProductLine::updateMultiplier(const float &target_per_min) {
	multiplier_ = target_per_min / (static_cast<float> (target_.amount()) * timing_coefficient_);
}

float ProductLine::calcPower() const {
    return multiplier_ * static_cast<float>(recipe_.machine().power());
}

std::vector<data::Item> ProductLine::calcIngredients() const {
    std::vector<data::Item> out = recipe_.ingredientList();
    for (auto &item : out) {
        item.setRate(multiplier_ * (static_cast<float>(item.amount()) * timing_coefficient_));
    }
    return out;
}

std::vector<data::Item> ProductLine::calcProducts() const {
    std::vector<data::Item> out = recipe_.productList();
    for (auto &item : out) {
        item.setRate(multiplier_ * (static_cast<float>(item.amount()) * timing_coefficient_));
    }
    return out;
}

} // namespace plan