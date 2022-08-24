/**
 * @project Satisfactory_Planner
 * @file Subfactory.cpp
 *
 * @author Jackson Miller
 * @date 2021-10-05
 * @copyright (c) 2021 Jackson Miller
 */

#include <random>

#include "plan/Subfactory.h"

namespace plan {

void to_json(nlohmann::json &json, const Subfactory &subfactory) {
    json["name"] = subfactory.label_;
    json["icon"] = subfactory.icon_string_;

    for (auto target = subfactory.targets_.cbegin(); target != subfactory.targets_.cend(); ++target) {
		json["targets"][target - subfactory.targets_.cbegin()] = **target;
    }

    for (auto byproduct = subfactory.byproducts_.cbegin(); byproduct != subfactory.byproducts_.cend(); ++byproduct) {
		json["byproducts"][byproduct - subfactory.byproducts_.cbegin()] = *byproduct;
    }

    for (auto ingredient = subfactory.ingredients_.cbegin(); ingredient != subfactory.ingredients_.cend(); ++ingredient) {
	    json["ingredients"][ingredient - subfactory.ingredients_.cbegin()] = **ingredient;
    }

	for (auto product_line = subfactory.product_lines_.cbegin(); product_line != subfactory.product_lines_.cend(); ++product_line) {
		json["product_lines"][product_line - subfactory.product_lines_.cbegin()] = **product_line;
	}
}

Subfactory::Subfactory(std::string label, std::string icon) :
    label_(std::move(label)),
    icon_string_(std::move(icon)) {
}

void Subfactory::addProductLine(const ProductLine& product_line) {
    product_lines_.emplace_back(std::make_unique<ProductLine>(product_line));

	if (!isTarget(product_lines_.back()->targetItem())) {
		for (auto ing = ingredients_.begin(); ing != ingredients_.end(); ++ing) {
			if ((*ing).get() == product_line.target()) {
				intermediates_.emplace_back(std::move(*ing));

				ingredients_.erase(ing);
			}
		}
	}
}

void Subfactory::addTarget(const TableItem& target_product) {
	// Check if this is already on the list
	// Combine with existing item if it is
	if (isTarget(target_product.target())) {
		addToTarget(target_product.target());

	} else {
		// Add to the list if it isn't
		targets_.emplace_back(std::make_unique<TableItem>(target_product));
	}
}

void Subfactory::addTarget(const data::Item& target_product) {
	addTarget(TableItem(target_product));
}

void Subfactory::addToTarget(const data::Item& item) {
	for (auto& existing : targets_) {
		if (existing->target() == item) {
			existing->addRate(item.rate());
		}
	}
}

void Subfactory::removeTargets(int start_index, int end_index) {
	targets_.erase(targets_.begin() + start_index, targets_.begin() + (end_index + 1));
}

void Subfactory::removeProductLines(int start_index, int end_index) {
	product_lines_.erase(product_lines_.begin() + start_index, product_lines_.begin() + (end_index) + 1);
}

float Subfactory::productRemainder(TableItem* target) const {
    float target_rate = target->rate();
    for (const auto &product : product_lines_) {
        if (product->target() == target) {
            target_rate -= product->actualOutputRate();
        }
    }
    return target_rate;
}

void Subfactory::checkTargetCompletion() {
	for (auto& target : targets_) {
		target->setCompletion(0);
		for (const auto& line : product_lines_) {
			if (target.get() == line->target()) {
				target->setCompletion(target->completion() + line->percent());
			}
		}
	}
}

void Subfactory::calculateTable() {
    for (auto& line : product_lines_) {
        line->calculate();
    }

	calculate();
	checkTargetCompletion();

    do {
        validate();
        for (auto& line: product_lines_) {
            if (!line->isValid()) {
                line->update();
	            calculate();
            }
        }
    } while (std::any_of(product_lines_.cbegin(), product_lines_.cend(),
                        [](const std::unique_ptr<ProductLine>& table_line){ return !table_line->isValid(); }));
}

void Subfactory::calculate() {
	// Clear existing byproducts and ingredients
	byproducts_.clear();
	ingredients_.clear();

	// Zero out ingredients as their rates will require updating
	for (auto& ingredient : ingredients_) {
		ingredient->setRate(0);
	}

	// Tabulate everything produced and demanded by the table
	std::vector<data::Item> produced;
	std::vector<data::Item> demanded;
	for (const auto& line : product_lines_) {
		// Combine existing products
		//  If this line's targetItem is in the existing list,
		if (std::any_of(produced.cbegin(), produced.cend(),
		                [&line](const data::Item& prod){ return line->targetItem() == prod; })) {

			// Combine its output with the output of the existing item
			for (auto& existing_item : produced) {
				if (existing_item == line->targetItem()) {
					existing_item.addRate(line->targetItem().rate());
				}
			}

		} else {

			// If this line's targetItem is not on the list already,
			// Add it in
			produced.push_back(line->targetItem());
		}

		// Do the same for byproducts
		if (line->hasByproduct() && line->useByproduct()) {
			if (std::any_of(produced.cbegin(), produced.cend(),
			                [&line](const data::Item& prod){ return line->byproduct() == prod; })) {
				for (auto& existing_item : produced) {
					if (existing_item == line->byproduct()) {
						existing_item.addRate(line->byproduct().rate());
					}
				}
			} else {
				produced.push_back(line->byproduct());
			}
		} else if (line->hasByproduct() && !line->useByproduct()) {

			byproducts_.push_back(line->byproduct());
		}

		// Ingredients
		for (const auto& line_ing : line->ingredients()) {
			if (std::any_of(demanded.cbegin(), demanded.cend(),
			                [line_ing](const data::Item& existing_ing){ return line_ing == existing_ing; })) {
				for (auto& existing_item : demanded) {
					existing_item.addRate(line_ing.rate());
				}
			} else {
				demanded.push_back(line_ing);
			}
		}
	}

	// Zero out intermediates
	for (auto& intermediate : intermediates_) {
		intermediate->setRate(0);
	}

	// Rectify demanded items with intermediate products
	for (const auto& demanded_item : demanded) {
		for (auto& intermediate_target : intermediates_) {
			if (demanded_item == intermediate_target->target()) {
				intermediate_target->addRate(demanded_item.rate());
			}
		}
	}

	// Byproducts - Anything produced that is not a target, intermediate, or ingredient, or an overproduction of an intermediate
	for (auto& produced_item : produced) {
		if (!isTarget(produced_item) && !isIntermediate(produced_item) &&
				(std::none_of(demanded.cbegin(), demanded.cend(),
				             [produced_item](const data::Item& demanded_item) {
					             return produced_item == demanded_item;
				             }))) {
			byproducts_.push_back(produced_item);

			// If the produced item is an intermediate AND was a demanded item
		} else if (isIntermediate(produced_item) &&
		           std::any_of(demanded.cbegin(), demanded.cend(),
		                       [produced_item](const data::Item& demanded_item) {
			                       return produced_item == demanded_item;
		                       })) {
			for (const auto& demanded_item : demanded) {
				// If the produced item produced more than was demanded
				if (produced_item == demanded_item && produced_item.rate() > demanded_item.rate()) {
					byproducts_.push_back(produced_item);
					byproducts_.back().setRate(produced_item.rate() - demanded_item.rate());
				}
			}
		}
	}

	// Subtract produced items from demanded items
	for (const auto& produced_item : produced) {
		for (auto& demanded_item : demanded) {
			if (produced_item == demanded_item) {
				demanded_item.addRate(-1 * produced_item.rate());
			}
		}
	}

	// Remaining demanded items are the subfactory's ingredients
	for (const auto& demanded_item : demanded) {
		if (demanded_item.rate() > 0) {
			// If this is already an ingredient, add its rate to the existing item
			if (isIngredient(demanded_item)) {
				for (auto& ingredient: ingredients_) {
					if (ingredient->target() == demanded_item) {
						ingredient->addRate(demanded_item.rate());
					}
				}

				// If not, add it to the list of ingredients
			} else {
				ingredients_.emplace_back(std::make_unique<TableItem>(demanded_item));
			}
		}
	}

	// FIXME: Adding a product line for an ingredient offset by a byproduct doesn't use the correct rate

}

void Subfactory::validate() {
    for (auto& product_line : product_lines_) {
        product_line->validate();
    }
}

float Subfactory::powerDraw() const {
	float power = 0.0;

	for (const auto& line : product_lines_) {
		power += line->power();
	}

	return power;
}

bool Subfactory::isOnTable(TableItem* target) const {
	return std::any_of(product_lines_.cbegin(), product_lines_.cend(),
	                   [target](const std::unique_ptr<ProductLine>& line) {
		                   return target == line->target();
	                   });
}

bool Subfactory::isTarget(const data::Item& target) const {
	return std::any_of(targets_.cbegin(), targets_.cend(),
	                   [target](const std::unique_ptr<TableItem>& product) {
		                   return target == product->target();
	                   });
}

bool Subfactory::isIntermediate(const data::Item& item) const {
	return std::any_of(intermediates_.cbegin(), intermediates_.cend(),
	                   [item](const std::unique_ptr<TableItem>& intermediate) {
		                   return item == intermediate->target();
	                   });
}

bool Subfactory::isIngredient(const data::Item& item) const {
	return std::any_of(ingredients_.cbegin(), ingredients_.cend(),
	                   [item](const std::unique_ptr<TableItem>& ingredient) {
		                   return item == ingredient->target();
	                   });
}

}