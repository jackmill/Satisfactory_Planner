/**
 * @project Satisfactory_Planner
 * @file Recipe.cpp
 *
 * @author Jackson Miller
 * @date 2021-09-19
 * @copyright (c) 2021 Jackson Miller
 */

#include "data/Recipe.h"

namespace data {

/**
 *
 * @param recipe_name
 * @param db
 */
Recipe::Recipe(const std::string &recipe_name, const DBMap &db) :
    class_name_(recipe_name) {

    // Get json entry for the recipe
    nlohmann::json recipe_json = db.at("Class'/Script/FactoryGame.FGRecipe'").at(recipe_name);

    // Display Name
    name_ = recipe_json.at("mDisplayName");

    // Check Alternate
    std::string alternate_token = "Alternate: ";
    is_alternate_ = (name_.find(alternate_token) != std::string::npos);

    // Manufacture time
    std::string manufacture_time = recipe_json.at("mManufactoringDuration");
    manufacturing_time_ = std::stof(manufacture_time);

    // Ingredients
    GenerateItemList(recipe_json.at("mIngredients"), db, ingredients_);

    // Products
    GenerateItemList(recipe_json.at("mProduct"), db, products_);

    // Building
    GenerateBuilding(recipe_json.at("mProducedIn"), db);

    // Set the machined flag
    if (produced_in_.has_value()) {
        is_machined_ = true;
    }
}

/**
 *
 * @param items_string
 * @param db
 * @param target_list
 */
void Recipe::GenerateItemList(const std::string &items_string, const DBMap &db, std::vector<Item> &target_list) {

    // Remove Outside Parentheses
    std::string items = items_string.substr(1, items_string.length() - 2);

    // Parse and assemble individual ingredients
    std::vector<std::string> ing_strs;
    std::string temp;
    for (const auto &character : items) {
        if (character == '(' || character == ',') {
            continue;
        } else {
            if (character == ')') {
                ing_strs.push_back(temp);
                temp = "";
            } else {
                temp += character;
            }
        }
    }

    // Use individual ingredient strings to populate member std::vector<Item> ingredients_
    for (const std::string &ingredient : ing_strs) {
        std::string class_name = ingredient.substr(ingredient.find('.') + 1, ingredient.find('\"', ingredient.find('.')) - (ingredient.find('.') + 1));

        std::string amt_token = "Amount=";
        int amt = std::stoi(ingredient.substr(ingredient.find(amt_token) + amt_token.length()));

        target_list.emplace_back(Item(class_name, amt, db));
    }
}

void Recipe::GenerateBuilding(const std::string &building_string, const DBMap &db) {
    std::string produced_in_list = building_string;

    // Remove enclosing parentheses
    try {
        produced_in_list = produced_in_list.substr(1, produced_in_list.length() - 2);
    } catch (const std::exception &e) {
        produced_in_list = "/Game/FactoryGame/Equipment/BuildGun/BP_BuildGun.BP_BuildGun_C";
    }

    // Parse string to separate comma-delineated list
    std::string temp;
    std::vector<std::string> bldg_list;
    for (auto character : produced_in_list) {
        if (character == ',') {
            bldg_list.emplace_back(temp);
            temp = "";
        } else {
            temp += character;
        }
    }
    bldg_list.emplace_back(temp);

    // Truncate each string to just Build_MakerThing_C or whatever
    for (auto &string : bldg_list) {
        string = string.substr(string.find('.') + 1);
    }

    // Find the option that's a building
    for (auto &bldg : bldg_list) {
        if (bldg != "BP_BuildGun_C" &&
            bldg != "FGBuildGun" &&
            bldg != "BP_WorkshopComponent_C" &&
            bldg != "BP_WorkBenchComponent_C" &&
            bldg != "FGBuildableAutomatedWorkBench" &&
            bldg != "Build_Converter_C" &&
            !bldg.empty()) {
            produced_in_ = Building(bldg, db);
            break;
        } else {
            produced_in_.reset();
        }
    }
}

//std::vector<std::string> Recipe::productList() const {
//    std::vector<std::string> product_list;
//    for (const auto &targetItem : targets_) {
//        product_list.push_back(targetItem.name());
//    }
//    return product_list;
//}

}