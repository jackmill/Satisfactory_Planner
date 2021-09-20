/**
 * @file Recipe.cpp
 * Created by jackm on 9/19/2021
 */

#include "data/Recipe.h"

namespace plannerData {

void from_json(const nlohmann::json &json, Recipe &recipe) {
	json.at("mDisplayName").get_to(recipe.name_);
	json.at("mManufacturingDuration").get_to(recipe.manufacturing_time_);
}

}