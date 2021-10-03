/**
 * @file Building.h
 * Created by jackm on 9/19/2021
 */

#ifndef SATISFACTORY_PLANNER_BUILDING_H
#define SATISFACTORY_PLANNER_BUILDING_H

#include <string>
#include "nlohmann/json.hpp"
#include "DBMap.h"

namespace data {

class Building {
  
  public:
//	Building(const std::string &building_name, const nlohmann::json &json_db);
    Building(const std::string &building_name, const DBMap &db);
	
	[[nodiscard]] std::string name() const { return name_; };
    [[nodiscard]] int power() const { return power_; };
    void setPower(const int &power) { power_ = power; };
  
  private:
	std::string name_;
    std::string class_name_;
	int power_;
};

}

#endif //SATISFACTORY_PLANNER_BUILDING_H
