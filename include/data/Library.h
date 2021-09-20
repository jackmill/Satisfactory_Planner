/**
 * @file Library.h
 * Created by jackm on 9/19/2021
 */

#ifndef SATISFACTORY_PLANNER_LIBRARY_H
#define SATISFACTORY_PLANNER_LIBRARY_H

#include <vector>
#include "nlohmann/json.hpp"

#include "Item.h"
#include "Building.h"
#include "Recipe.h"

namespace plannerData {

class Library {
  public:
	Library(const nlohmann::json &json);
	
  private:
	std::vector<Item> items_;
    std::vector<Building> buildings_;
	std::vector<Recipe> recipes_;
};

}

#endif //SATISFACTORY_PLANNER_LIBRARY_H
