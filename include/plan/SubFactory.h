//
// Created by Jackson Miller on 9/27/21.
//

#ifndef SATISFACTORY_PLANNER_SUBFACTORY_H
#define SATISFACTORY_PLANNER_SUBFACTORY_H

#include <string>
#include <vector>

#include "data/Library.h"

namespace plan {

class Subfactory {
  public:

  private:
    // Container of FloorSlots
    std::string label_;
    std::vector<Item> target_products_;

};

} // namespace plan

#endif //SATISFACTORY_PLANNER_SUBFACTORY_H
