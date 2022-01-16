/**
 * @project Satisfactory_Planner
 * @file Subfactory.cpp
 *
 * @author Jackson Miller
 * @date 2021-10-05
 * @copyright (c) 2021 Jackson Miller
 */

#include <random>
#include <sstream>

#include "plan/Subfactory.h"

namespace plan {

void to_json(nlohmann::json &json, const Subfactory &subfactory) {
    json["name"] = subfactory.label_;
    json["icon"] = subfactory.icon_string_;

    for (auto target = subfactory.targets_.cbegin(); target != subfactory.targets_.cend(); ++target) {
		json["targets"][target - subfactory.targets_.cbegin()] = **target;
    }

    for (auto byproduct = subfactory.byproducts_.cbegin(); byproduct != subfactory.byproducts_.cend(); ++byproduct) {
		json["byproducts"][byproduct - subfactory.byproducts_.cbegin()] = **byproduct;
    }

    for (auto ingredient = subfactory.ingredients_.cbegin(); ingredient != subfactory.ingredients_.cend(); ++ingredient) {
	    json["ingredients"][ingredient - subfactory.ingredients_.cbegin()] = **ingredient;
    }

    json["product_lines"] = subfactory.product_lines_;
}

Subfactory::Subfactory(std::string label, std::string icon) :
    label_(std::move(label)),
    icon_string_(std::move(icon)) {
}

void Subfactory::addProductLine(const ProductLine& product_line) {
    product_lines_.emplace_back(product_line);
}

void Subfactory::addTarget(const std::shared_ptr<ProductTarget>& target_product) {
	targets_.emplace_back(target_product);
}

float Subfactory::targetRemainder(const std::shared_ptr<ProductTarget>& target) const {
    float target_rate = target->rate();
    for (const auto &product : product_lines_) {
        if (product.target() == target) {
            target_rate -= product.productOutput();
        }
    }
    return target_rate;
}

bool Subfactory::isTarget(const std::shared_ptr<ProductTarget>& item) const {
    return std::any_of(product_lines_.cbegin(), product_lines_.cend(),
                       [item] (const plan::ProductLine& line){ return line.target() == item; });
}

std::vector<std::shared_ptr<ProductTarget>> Subfactory::ingredientsNotOnTable() const {
    std::vector<std::shared_ptr<ProductTarget>> out;

    for (const auto& ingredient : ingredients_) {
        // TODO: Allow separation of ingredient-targeted product lines
		if (!isTarget(ingredient)) {
			out.push_back(ingredient);
        }
    }

    return out;
}

void Subfactory::updateIngredients() {
    // Zero out existing ingredients
    for (const auto& ingredient : ingredients_) {
        ingredient->setRate(0);
    }

    // Tally ingredients
    for (const auto& line : product_lines_) {
        for (const auto& line_ingredient : line.ingredients()) {

            if (!ingredients_.empty()) {
                bool exists = false;
                for (auto& ingredient : ingredients_) {

                    if (line_ingredient == ingredient->target()) {
                        exists = true;
                        ingredient->setRate(ingredient->rate() + line_ingredient.rate());
                    }

                }

                if (!exists) {
                    ingredients_.emplace_back(std::make_shared<ProductTarget>(line_ingredient));
                }

            } else {
                ingredients_.emplace_back(std::make_shared<ProductTarget>(line_ingredient));
            }

        }
    }

    // Find and remove existing ingredients that are not in the table
    // If the item's rate is 0, nothing added to it in the previous for loop, so it's not on the table
    for (auto ingredient = ingredients_.cbegin(); ingredient != ingredients_.cend(); ++ingredient) {
        if ((*ingredient)->rate() <= 0) {
            ingredients_.erase(ingredient);
        }
    }
}


void Subfactory::updateByproducts() {
    byproducts_.clear();

    // Find the byproducts
    std::vector<data::Item> all_byproducts;
    for (const auto &line : product_lines_) {
        for (const auto &line_prod : line.calcProducts()) {
            if (line_prod != line.target()->target()) {
                if (all_byproducts.empty()) {
                    all_byproducts.emplace_back(line_prod);
                } else {
                    bool exists = false;
                    for (auto &byproduct : all_byproducts) {
                        if (line_prod == byproduct) {
                            byproduct.setRate(byproduct.rate() + line_prod.rate());
                            exists = true;
                        }
                    }
                    if (!exists) {
                        all_byproducts.emplace_back(line_prod);
                    }
                }
            }
        }
    }

}
/*
void Subfactory::updateIngredients() {
    ingredients_.clear();
    byproducts_.clear();

    // Make a list of the total output of the subfactory
    std::vector<data::Item> output;

    // Make a list of the total consumption of the subfactory
    std::vector<data::Item> consumed_items;
    for (const auto &line : product_lines_) {
        for (const auto &line_prod : line.calcProducts()) {
            // If the item is already in the list, add the rate to the existing total
            // Else add it to the list
            if (output.empty()) {
                output.emplace_back(line_prod);
            } else {
                // Check for a duplicate
                bool exists = false;
                for (auto &output_prod : output) {
                    // If we find a duplicate, add to its rate
                    if (line_prod == output_prod) {
                        output_prod.setRate(output_prod.rate() + line_prod.rate());
                        exists = true;
                    }
                }
                // If there wasn't a duplicate when we get to the end of the outputs loop,
                // add it in
                if (!exists) {
                    output.emplace_back(line_prod);
                }
            }
        }

        for (const auto &line_ingr : line.calcIngredients()) {
            // If the item is already in the list, add the rate to the existing total
            // Else add it to the list
            if (consumed_items.empty()) {
                consumed_items.emplace_back(line_ingr);
            } else {
                bool exists = false;
                for (auto &consumed_ingr: consumed_items) {
                    if (line_ingr == consumed_ingr) {
                        consumed_ingr.setRate(consumed_ingr.rate() + line_ingr.rate());
                        exists = true;
                    }
                }
                if (!exists) {
                    consumed_items.emplace_back(line_ingr);
                }
            }
        }
    }

    // Subtract total output from total consumption
    for (auto ingredient = consumed_items.begin(); ingredient != consumed_items.end(); ++ingredient) {
        for (const auto &product : output) {
            if (product == *ingredient) {
                ingredient->setRate(ingredient->rate() - product.rate());

                // If the ingredient rate is zero, remove it from the list
                if (ingredient->rate() <= 0) {
                    consumed_items.erase(ingredient);
                }
            }
        }
    }

    for (const auto& consumed : consumed_items) {
        ingredients_.push_back(std::make_shared<data::Item>(consumed));
    }
}
*/

void Subfactory::calculate() {
    for (auto& line : product_lines_) {
        line.calculate();
    }
    updateIngredients();
    updateByproducts();


    do {
        validate();
        for (auto& line: product_lines_) {
            if (!line.isValid()) {
                line.update();
                updateIngredients();
                updateByproducts();
            }
        }
    } while (std::any_of(product_lines_.cbegin(), product_lines_.cend(),
                        [](const plan::ProductLine& table_line){ return !table_line.isValid(); }));
}

void Subfactory::validate() {
    for (auto& product_line : product_lines_) {
        product_line.validate();
    }
}

}