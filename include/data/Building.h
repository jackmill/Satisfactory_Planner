/**
 * @file Building.h
 * Created by jackm on 9/19/2021
 */

#ifndef SATISFACTORY_PLANNER_BUILDING_H
#define SATISFACTORY_PLANNER_BUILDING_H

#include <string>

namespace plannerData {

class Building {
  public:
	Building();
	
	std::string name() { return name_; };
  
  private:
	std::string name_;
	int power_;
};

}

#endif //SATISFACTORY_PLANNER_BUILDING_H
