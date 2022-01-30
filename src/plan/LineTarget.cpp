/**
 * @project Satisfactory_Planner
 * @file LineTarget.cpp
 * 
 * @author Jackson Miller
 * @date 2022-01-15
 * @copyright (c) 2022 Jackson Miller
 */

#include "plan/LineTarget.h"

namespace plan {

void to_json(nlohmann::json& json, const LineTarget& product_target) {
	json["id"] = to_string(product_target.id_);
	json["item"] = product_target.target_item_;
}

LineTarget::LineTarget(const data::Item& target) :
		target_item_(target){
	id_ = uuids::uuid_system_generator{}();
}

LineTarget::LineTarget(uuids::uuid id, const data::Item& target):
		id_(id),
		target_item_(target) {
}

void LineTarget::addProductLineReference(uuids::uuid contributor) {
	associated_product_lines_.emplace_back(contributor);
}

bool LineTarget::isAssociated(const uuids::uuid& contributor) const {
	return std::any_of(associated_product_lines_.cbegin(),
					   associated_product_lines_.cend(),
					   [contributor](const uuids::uuid& line) {
		return contributor == line;
	});
}

void LineTarget::clearAssociated() {
	associated_product_lines_.clear();
}

} // namespace plan