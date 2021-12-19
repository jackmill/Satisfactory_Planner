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
    nlohmann::json json;

    json["subfactories"] = factory.subfactories_;

    out << json;
    return out;
}

void Factory::save(const std::string &file_path) const {
    std::ofstream file(file_path);
    if (!file.is_open() || file.fail()) {
        throw std::runtime_error("Failed to open file for writing");
    }

    file << *this;
    file.close();
}

void Factory::setSubfactories(std::vector<Subfactory> subfactories) {
    subfactories_.clear();
    subfactories_ = std::move(subfactories);
}

}