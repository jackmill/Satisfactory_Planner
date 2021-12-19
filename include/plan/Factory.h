/**
 * @project Satisfactory_Planner
 * @file Factory.h
 *
 * @author Jackson Miller
 * @date 2021-09-25
 * @copyright (c) 2021 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_FACTORY_H
#define SATISFACTORY_PLANNER_FACTORY_H

#include <vector>

#include "Subfactory.h"
#include "nlohmann/json.hpp"

namespace plan {

class Factory {
    friend std::ostream &operator<< (std::ostream &out, const Factory &factory);

  public:
    Factory() = default;

    void save(const std::string &file_path) const;

    void setSubfactories(std::vector<Subfactory> subfactories);

    std::vector<Subfactory> subfactories_;
};

} // namespace plan

#endif //SATISFACTORY_PLANNER_FACTORY_H
