/**
 * @file Recipe.h
 * Created by jackm on 9/19/2021
 */

#ifndef SATISFACTORY_PLANNER_RECIPE_H
#define SATISFACTORY_PLANNER_RECIPE_H

#include <vector>
#include <string>
#include "nlohmann/json.hpp"

#include "data/Item.h"
#include "data/Building.h"

namespace plannerData {

class Recipe {
  friend void from_json(const nlohmann::json &json, Recipe &recipe);
  
  public:
	
	
	std::string name() const { return name_; };
	int time() const { return manufacturing_time_; };
	
	
  private:
	std::string name_;
	std::vector<Item> ingredients_;
	std::vector<Item> products_;
	int manufacturing_time_;
	std::string produced_in_;
	
	bool in_machine = false;
};

}
#endif //SATISFACTORY_PLANNER_RECIPE_H
