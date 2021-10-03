//
// Created by Jackson Miller on 9/25/21.
//

#ifndef SATISFACTORY_PLANNER_FACTORY_H
#define SATISFACTORY_PLANNER_FACTORY_H

#include <vector>

#include "Subfactory.h"

namespace plan {

class Factory {
  public:
    Factory() = default;

    std::vector<Subfactory> subfactories;
};

} // namespace plan

#endif //SATISFACTORY_PLANNER_FACTORY_H
