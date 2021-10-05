/**
 * @file Building.cpp
 * Created by jackm on 9/19/2021
 */

#include "data/Building.h"

namespace data {

Building::Building(const std::string &building_name, const DBMap &db) :
    class_name_(building_name) {

    name_ = findKey(class_name_, "mDisplayName", db);
    std::string power_string = findKey(class_name_, "mPowerConsumption", db);
    power_ = std::stoi(power_string);
}

}