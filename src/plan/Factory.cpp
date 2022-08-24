/**
 * @project Satisfactory_Planner
 * @file Factory.cpp
 * 
 * @author Jackson Miller
 * @date 2021-11-09
 * @copyright (c) 2021 Jackson Miller
 */

#include <fstream>

#include "plan/Factory.h"

namespace plan {

std::ostream &operator<<(std::ostream &out, const Factory &factory) {
    nlohmann::json output_json;

    for (auto subfactory = factory.subfactories_.cbegin(); subfactory != factory.subfactories_.cend(); ++subfactory) {
	    output_json["subfactories"][subfactory - factory.subfactories_.cbegin()] = **subfactory;
    }

    out << output_json;
    return out;
}

std::istream &operator>>(std::istream &in, Factory &factory) {
    // Make sure there's a DBMap to generate from
    assert(factory.db_.has_value());
	// TODO: Redo this
/*
    nlohmann::json json;
    try {
        in >> json;
    } catch (const nlohmann::json::parse_error &e) {
        throw e;
    }
    if (!json.contains("subfactories")) {
        throw std::runtime_error("Missing 'subfactories' key -- not a valid factory file");
    }

    decltype(plan::Factory::subfactories_) new_subfactories;
    for (const auto& json_subfactory : json.at("subfactories")) {
        // Name and TableIcon
        Subfactory temp(json_subfactory.at("name"), json_subfactory.at("icon"));

        // Targets
        for (const auto &json_target : json_subfactory.at("targets")) {
            data::Item temp_item(json_target.at("item").at("class_name"), factory.db_.value());
            temp_item.setRate(json_target.at("item").at("rate"));
            temp.addTarget(
                    std::make_shared<TableItem>(uuids::uuid::from_string(json_target.at("id").get<std::string>()),
                                                temp_item));
        }

        // Byproducts
        if (json_subfactory.contains("byproducts")) {
            for (const auto& json_target: json_subfactory.at("byproducts")) {
                data::Item temp_item(json_target.at("item").at("class_name"), factory.db_.value());
                temp_item.setRate(json_target.at("item").at("rate"));
                temp.byproducts_.emplace_back(std::make_shared<TableItem>(uuids::uuid::from_string(json_target.at("id").get<std::string>()), temp_item));
            }
        }

        // Ingredients
        if (json_subfactory.contains("ingredients")) {
            for (const auto& json_target: json_subfactory.at("ingredients")) {
                data::Item temp_item(json_target.at("item").at("class_name"), factory.db_.value());
                temp_item.setRate(json_target.at("item").at("rate"));
                temp.ingredients_.emplace_back(std::make_shared<TableItem>(uuids::uuid::from_string(json_target.at("id").get<std::string>()), temp_item));
            }
        }

        // Product Lines
        if (json_subfactory.contains("product_lines")) {
            for (const auto& json_line: json_subfactory.at("product_lines")) {

                // Search for the target of this targetItem line in the targets and ingredients
                bool found_target = false;
                for (const auto& target: temp.targets_) {
                    if (uuids::uuid::from_string(json_line.at("target").get<std::string>()) == target->id()) {
                        ProductLine temp_line(target, data::Recipe(json_line.at("recipe"), factory.db_.value()));
                        temp_line.setDone(json_line.at("done"));
	                    temp_line.setClockSpeed(json_line.at("clock_speed"));
						temp_line.setPercent(json_line.at("percent"));
                        temp.product_lines_.emplace_back(temp_line);

                        found_target = true;
                        break;
                    }
                }

                // If we found the target earlier, we don't need to look through ingredients for it
                if (!found_target) {
                    for (const auto& ingredient: temp.ingredients_) {
                        if (uuids::uuid::from_string(json_line.at("target").get<std::string>()) == ingredient->id()) {
                            ProductLine temp_line(ingredient,
                                                  data::Recipe(json_line.at("recipe"), factory.db_.value()));
                            temp_line.setDone(json_line.at("done"));
	                        temp_line.setClockSpeed(json_line.at("clock_speed"));
	                        temp_line.setPercent(json_line.at("percent"));
                            temp.product_lines_.emplace_back(temp_line);

                            break;
                        }
                    }
                }
            }
        }

        // Run a calculation just to make sure everything's right
        temp.calculateTable();
        new_subfactories.emplace_back(std::make_shared<Subfactory>(temp));
    }
    factory.subfactories_ = new_subfactories;
*/
    return in;
}

Factory::Factory(const std::string& file_path, const data::DBMap& db) {
    db_ = db;

    std::ifstream file(file_path);
    if (!file.is_open() || file.fail()) {
        throw std::runtime_error("Failed to open file for reading");
    }
    file >> *this;
    file.close();
    db_.reset();
}

void Factory::save(const std::string &file_path) const {
    std::ofstream file(file_path);
    if (!file.is_open() || file.fail()) {
        throw std::runtime_error("Failed to open file for writing");
    }

    file << *this;
    file.close();
}

void Factory::addSubfactory(const Subfactory& new_subfactory) {
	subfactories_.emplace_back(std::make_unique<Subfactory>());
	subfactories_.back()->setLabel(new_subfactory.label());
	subfactories_.back()->setIcon(new_subfactory.icon());
}

}