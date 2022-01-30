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
    json["done"] = product_line.complete_;
    json["target"] = uuids::to_string(product_line.target_->id());
    json["recipe"] = product_line.recipe_.className();
	json["clock_speed"] = product_line.clock_speed_ * 100;
	json["percent"] = product_line.percentage_ * 100;
}

ProductLine::ProductLine(std::shared_ptr<LineTarget> target, data::Recipe recipe) :
        target_(std::move(target)),
        recipe_(std::move(recipe)),
        multiplier_(1) {
    id_ = uuids::uuid_system_generator{}();
    changeRecipe(recipe_);
}

void ProductLine::changeRecipe(const data::Recipe &recipe) {
	recipe_ = recipe;
	
	// Update the numbers
    timing_coefficient_ = static_cast<float> (60.0 / recipe_.time());
	updateMultiplier(target_->rate());
    calculate();
}

void ProductLine::updateMultiplier(const float &target_per_min) {
	int target_recipe_amount;
    for (const auto &product : recipe_.productList()) {
        if (product == target_->target()) {
            target_recipe_amount = product.amount();
        }
    }

    multiplier_ = multiplierCalculation(target_per_min, target_recipe_amount);
}

float ProductLine::calcPower() const {
    float base_consumption = multiplier_ * static_cast<float>(recipe_.machine().power());

	// Power usage = base_consumption * (clock_speed_ / 100) ^ 1.6
	return static_cast<float>(base_consumption * std::pow(clock_speed_, 1.6));
}

std::vector<data::Item> ProductLine::calcIngredients() const {
    std::vector<data::Item> out = recipe_.ingredientList();
    for (auto &item : out) {
        calcRate(item);
    }
    return out;
}

std::vector<data::Item> ProductLine::calcProducts() const {
    std::vector<data::Item> out = recipe_.productList();
    for (auto &item : out) {
        calcRate(item);
    }
    return out;
}

void ProductLine::calculate() {
    updateMultiplier(target_->rate());

    ingredients_ = calcIngredients();
    power_ = calcPower();

    std::vector<data::Item> products = calcProducts();
    for (auto& prod : products) {
        if (prod != target_->target()) {
            byproduct_ = std::move(prod);
        }
    }
}

void ProductLine::update() {
    updateMultiplier(target_->rate());
    power_ = calcPower();

    for (auto& ingredient : ingredients_) {
        calcRate(ingredient);
    }

    if (byproduct_.has_value()) {
        calcRate(byproduct_.value());
    }
}

void ProductLine::validate() {
    valid_ = false;

    int target_recipe_amount;
    for (const auto &product : recipe_.productList()) {
        if (product == target_->target()) {
            target_recipe_amount = product.amount();
        }
    }

    if (multiplier_ != multiplierCalculation(target_->rate(), target_recipe_amount)) {
        return;
    }

    for (const auto& ingredient : ingredients_) {
        if (ingredient.rate() != itemRateCalculation(ingredient.amount())) {
            return;
        }
    }
    if (byproduct_.has_value()) {
        if (byproduct_.value().rate() !=
		        itemRateCalculation(byproduct_.value().amount())) {
            return;
        }
    }
    if (power_ != calcPower()) {
        return;
    }

    valid_ = true;
}

void ProductLine::calcRate(data::Item& item) const {
    item.setRate(itemRateCalculation(item.amount()));
}

float ProductLine::itemRateCalculation(int item_amount) const {
	return (multiplier_ * (static_cast<float>(item_amount) * timing_coefficient_)) * clock_speed_;
}

float ProductLine::multiplierCalculation(float target_rate, int target_item_amount) const {
	return ((target_rate / (static_cast<float> (target_item_amount) * timing_coefficient_)) / clock_speed_) * percentage_;
}

} // namespace plan