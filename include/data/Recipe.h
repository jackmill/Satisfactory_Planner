/**
 * @project Satisfactory_Planner
 * @file Recipe.h
 *
 * @author Jackson Miller
 * @date 2021-09-19
 * @copyright (c) 2021 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_RECIPE_H
#define SATISFACTORY_PLANNER_RECIPE_H

#include <vector>
#include <string>
#include <optional>
#include "nlohmann/json.hpp"

#include "data/Item.h"
#include "data/Building.h"

namespace data {

class Recipe {
  public:
    Recipe(const std::string &recipe_name, const DBMap &db);
	
	[[nodiscard]] std::string name() const { return name_; };
    [[nodiscard]] std::string className() const { return class_name_; };
	[[nodiscard]] int time() const { return manufacturing_time_; };
    [[nodiscard]] bool isMachined() const { return is_machined_; };
    [[nodiscard]] bool isAlternate() const { return is_alternate_; };
    [[nodiscard]] std::vector<Item> ingredientList() const { return ingredients_; };
    [[nodiscard]] std::vector<Item> productList() const { return products_; };
    [[nodiscard]] Building machine() const { return produced_in_.value(); };
	
	
  private:
	std::string class_name_;
    std::string name_;
	std::vector<Item> ingredients_;
	std::vector<Item> products_;
	int manufacturing_time_;
    std::optional<Building> produced_in_;

    bool is_machined_ = false;
    bool is_alternate_ = false;

    // Constructor helpers
    static void GenerateItemList(const std::string &items_string, const DBMap &db, std::vector<Item> &target_list);
    void GenerateBuilding(const std::string &building_string, const DBMap &db);
};

}
#endif //SATISFACTORY_PLANNER_RECIPE_H
