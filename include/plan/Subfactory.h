//
// Created by Jackson Miller on 9/27/21.
//

#ifndef SATISFACTORY_PLANNER_SUBFACTORY_H
#define SATISFACTORY_PLANNER_SUBFACTORY_H

#include <string>
#include <vector>

#include "ProductLine.h"
#include "data/Library.h"

namespace plan {

class Subfactory {
  public:
	
	

  private:
    std::string label_;
    std::string icon_string_;
    std::vector<Item> target_products_;
	std::vector<Subfactory> product_lines_;

};

} // namespace plan

#endif //SATISFACTORY_PLANNER_SUBFACTORY_H
