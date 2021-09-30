/**
 * @file Recipe.h
 * Created by jackm on 9/19/2021
 */

#ifndef SATISFACTORY_PLANNER_RECIPE_H
#define SATISFACTORY_PLANNER_RECIPE_H

#include <vector>
#include <string>
#include <optional>
#include "nlohmann/json.hpp"

#include "data/Item.h"
#include "data/Building.h"

namespace gameData {

class Recipe {
  public:
    Recipe(const std::string &recipe_name, const DBMap &db);
	
	std::string name() const { return name_; };
    std::string className() const { return class_name_; };
	int time() const { return manufacturing_time_; };
    bool isMachined() const { return is_machined_; };
    bool isAlternate() const { return is_alternate_; };
    std::vector<Item> ingredientList() const { return ingredients_; };
    std::vector<Item> productList() const { return products_; };
	
	
  private:
	std::string class_name_;
    std::string name_;
	std::vector<Item> ingredients_;
	std::vector<Item> products_;
	int manufacturing_time_;
    std::optional<Building> produced_in_;

    bool is_machined_ = false;
    bool is_alternate_ = false;
    // TODO: FICSMAS check

    // Constructor helpers
    static void GenerateItemList(const std::string &items_string, const DBMap &db, std::vector<Item> &target_list);
    void GenerateBuilding(const std::string &building_string, const DBMap &db);
};

}
#endif //SATISFACTORY_PLANNER_RECIPE_H
