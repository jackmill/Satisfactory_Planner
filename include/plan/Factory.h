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

namespace plan {

class Factory {
  public:
    Factory() = default;

    std::vector<Subfactory> subfactories_;
};

} // namespace plan

#endif //SATISFACTORY_PLANNER_FACTORY_H
