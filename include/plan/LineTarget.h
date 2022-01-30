/**
 * @project Satisfactory_Planner
 * @file LineTarget.h
 * 
 * @author Jackson Miller
 * @date 2022-01-15
 * @copyright (c) 2022 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_LINETARGET_H
#define SATISFACTORY_PLANNER_LINETARGET_H

#include "uuid.h"
#include "data/Item.h"

namespace plan {

class ProductLine;

class LineTarget {
	friend void to_json(nlohmann::json &json, const LineTarget &product_target);

  public:
	explicit LineTarget(const data::Item& target);
	LineTarget(uuids::uuid id, const data::Item& target);

	[[nodiscard]] uuids::uuid id() const { return id_; };

	[[nodiscard]] data::Item target() const { return target_item_; };
	[[nodiscard]] std::string name() const { return target_item_.name(); };
	[[nodiscard]] std::string className() const { return target_item_.className(); };
	[[nodiscard]] float completion() const { return completion_; };
	void setCompletion(float comp) { completion_ = comp; };

	[[nodiscard]] int amount() const { return target_item_.amount(); };
	[[nodiscard]] float rate() const { return target_item_.rate(); };
	void setRate(const float& rate) { target_item_.setRate(rate); };
	void clearAmount() { target_item_.clearAmount(); };

	void replaceWith(const data::Item& rhs) { target_item_.replaceWith(rhs); };

	[[nodiscard]] std::vector<uuids::uuid> associatedProductLines() const { return associated_product_lines_; };
	void addProductLineReference(uuids::uuid contributor);
	[[nodiscard]] bool isAssociated(const uuids::uuid& contributor) const;
	void clearAssociated();

  private:
	uuids::uuid id_;
    data::Item target_item_;
	float completion_ = 0.0;

	std::vector<uuids::uuid> associated_product_lines_;
};

} // namespace plan

#endif //SATISFACTORY_PLANNER_LINETARGET_H
