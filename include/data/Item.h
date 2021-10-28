/**
 * @project Satisfactory_Planner
 * @file Item.h
 *
 * @author Jackson Miller
 * @date 2021-09-17
 * @copyright (c) 2021 Jackson Miller
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

    bool operator== (const Item &rhs) const { return this->class_name_ == rhs.class_name_; };
    bool operator!= (const Item &rhs) const { return !(this->class_name_ == rhs.class_name_); };
    bool operator<(const Item &rhs) const { return name_ < rhs.name_; }
    bool operator>(const Item &rhs) const { return rhs < *this; }
    bool operator<=(const Item &rhs) const { return !(rhs < *this); }
    bool operator>=(const Item &rhs) const { return !(*this < rhs); }
    Item& operator= (const Item &rhs) = default;

    [[nodiscard]] std::string name() const { return name_; };
    [[nodiscard]] std::string className() const { return class_name_; };
	void setName(const std::string &name) { name_ = name; };
	
	[[nodiscard]] int amount() const;
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
