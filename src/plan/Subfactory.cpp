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

    for (auto target = subfactory.products_.cbegin(); target != subfactory.products_.cend(); ++target) {
		json["targets"][target - subfactory.products_.cbegin()] = **target;
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

void Subfactory::addProduct(const std::shared_ptr<LineTarget>& target_product) {
	products_.emplace_back(target_product);
}

float Subfactory::productRemainder(const std::shared_ptr<LineTarget>& target) const {
    float target_rate = target->rate();
    for (const auto &product : product_lines_) {
        if (product.target() == target) {
            target_rate -= product.productOutput();
        }
    }
    return target_rate;
}

bool Subfactory::isOnTable(const std::shared_ptr<LineTarget>& item) const {
    return std::any_of(product_lines_.cbegin(), product_lines_.cend(),
                       [item] (const plan::ProductLine& line){ return line.target() == item; });
}

std::vector<std::shared_ptr<LineTarget>> Subfactory::ingredientsNotOnTable() const {
    std::vector<std::shared_ptr<LineTarget>> out;

    for (const auto& ingredient : ingredients_) {
		if (!isOnTable(ingredient)) {
			out.push_back(ingredient);
        }
    }

    return out;
}

void Subfactory::updateIngredients() {
    // Zero out existing ingredients
    for (const auto& ingredient : ingredients_) {
        ingredient->setRate(0);
		ingredient->clearAssociated();
    }

    // Tally ingredients
    for (auto& line : product_lines_) {
        for (const auto& line_ingredient : line.ingredients()) {

            if (!ingredients_.empty()) {
                bool exists = false;
                for (auto& ingredient : ingredients_) {

                    if (line_ingredient == ingredient->target()) {
                        exists = true;
                        ingredient->setRate(ingredient->rate() + line_ingredient.rate());
						ingredient->addProductLineReference(line.id());
                    }

                }

                if (!exists) {
                    ingredients_.emplace_back(std::make_shared<LineTarget>(line_ingredient));
					ingredients_.at(ingredients_.size() - 1)->addProductLineReference(line.id());
                }

            } else {
                ingredients_.emplace_back(std::make_shared<LineTarget>(line_ingredient));
	            ingredients_.at(ingredients_.size() - 1)->addProductLineReference(line.id());
            }

        }
    }

    // Find and remove existing ingredients that are not in the table
    // If the item's rate is 0, nothing added to it in the previous for loop, so it's not on the table
    ingredients_.erase(std::remove_if(ingredients_.begin(), ingredients_.end(),
									  [](const std::shared_ptr<LineTarget>& ingredient){
											return ingredient->rate() <=0; }),
					   ingredients_.end());

	// Set product lines' changeable-ness
	//  If a product line has ingredients that are the targets of other product lines,
	//  they may not be deleted or changed
	resetChangeability();
	for (const auto& ingredient : ingredients_) {
		if (isOnTable(ingredient)) {
			for (auto& product_line: product_lines_) {
				if (ingredient->isAssociated(product_line.id())) {
					product_line.setChangeable(false);
				}
			}
		}
	}
}

void Subfactory::resetChangeability() {
	for (auto& line : product_lines_) {
		line.setChangeable(true);
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

void Subfactory::checkTargetCompletion() {
	for (auto& target : products_) {
		target->setCompletion(0);
		for (const auto& line : product_lines_) {
			if (target == line.target()) {
				target->setCompletion(target->completion() + line.percent());
			}
		}
	}
}

void Subfactory::calculate() {
    for (auto& line : product_lines_) {
        line.calculate();
    }
    updateIngredients();
    updateByproducts();
	checkTargetCompletion();

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