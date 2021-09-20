/**
 * @file Item.h
 * Created by jackm on 9/17/2021
 */

#ifndef SATISFACTORY_PLANNER_ITEM_H
#define SATISFACTORY_PLANNER_ITEM_H

#include <string>
#include <optional>

namespace plannerData {

class Item {
  public:
	explicit Item(std::string name);
	
	std::string name() { return name_; };
	void setName(const std::string &name) { name_ = name; };
	
	int amount();
	void setAmount(const int &amount);
  
  private:
	std::string name_;
	std::optional<int> amount_;
	
};

} // namespace plannerData

#endif //SATISFACTORY_PLANNER_ITEM_H
