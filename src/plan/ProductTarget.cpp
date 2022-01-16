/**
 * @project Satisfactory_Planner
 * @file ProductTarget.cpp
 * 
 * @author Jackson Miller
 * @date 2022-01-15
 * @copyright (c) 2022 Jackson Miller
 */

#include "plan/ProductTarget.h"

namespace plan {

void to_json(nlohmann::json& json, const ProductTarget& product_target) {
	json["id"] = to_string(product_target.id_);
	json["item"] = product_target.target_item_;
}

ProductTarget::ProductTarget(const data::Item& target) :
		target_item_(target){
	id_ = uuids::uuid_system_generator{}();
}

ProductTarget::ProductTarget(uuids::uuid id, const data::Item& target):
		id_(id),
		target_item_(target) {

}

} // namespace plan