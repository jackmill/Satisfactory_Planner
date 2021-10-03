/**
 * @file Item.h
 * Created by jackm on 9/17/2021
 */

#ifndef SATISFACTORY_PLANNER_ITEM_H
#define SATISFACTORY_PLANNER_ITEM_H

#include <string>
#include <optional>
#include <unordered_map>
#include "nlohmann/json.hpp"

#include "DBMap.h"

namespace data {

class Item {
  public:
    Item(const std::string &class_name, const DBMap &db);
    Item(const std::string &class_name, const int &amount, const DBMap &db);

    inline bool operator== (const Item &rhs) const { return this->class_name_ == rhs.class_name_; };
    inline bool operator!= (const Item &rhs) const { return !(this->class_name_ == rhs.class_name_); };
	
	std::string name() const { return name_; };
    std::string className() const { return class_name_; };
	void setName(const std::string &name) { name_ = name; };
	
	int amount() const;
	void setAmount(const int &amount);
    void clearAmount() { amount_.reset(); };
  
  private:
	std::string name_;
    std::string class_name_;
    bool is_liquid_ = false;
	std::optional<int> amount_;
	
};

} // namespace data

#endif //SATISFACTORY_PLANNER_ITEM_H
