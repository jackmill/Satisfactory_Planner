/**
 * @project Satisfactory_Planner
 * @file ProductTarget.h
 * 
 * @author Jackson Miller
 * @date 2022-01-15
 * @copyright (c) 2022 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_PRODUCTTARGET_H
#define SATISFACTORY_PLANNER_PRODUCTTARGET_H

#include "uuid.h"
#include "data/Item.h"

namespace plan {

class ProductTarget {
	friend void to_json(nlohmann::json &json, const ProductTarget &product_target);

  public:
	explicit ProductTarget(const data::Item& target);
	ProductTarget(uuids::uuid id, const data::Item& target);

	[[nodiscard]] uuids::uuid id() const { return id_; };

	[[nodiscard]] data::Item target() const { return target_item_; };
	[[nodiscard]] std::string name() const { return target_item_.name(); };
	[[nodiscard]] std::string className() const { return target_item_.className(); };

	[[nodiscard]] int amount() const { return target_item_.amount(); };
	[[nodiscard]] float rate() const { return target_item_.rate(); };
	void setRate(const float& rate) { target_item_.setRate(rate); };
	void clearAmount() { target_item_.clearAmount(); };

	void replaceWith(const data::Item& rhs) { target_item_.replaceWith(rhs); };

  private:
	uuids::uuid id_;
    data::Item target_item_;
};

} // namespace plan

#endif //SATISFACTORY_PLANNER_PRODUCTTARGET_H
