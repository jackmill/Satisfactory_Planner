/**
 * @project Satisfactory_Planner
 * @file TableItem.cpp
 * 
 * @author Jackson Miller
 * @date 2022-01-15
 * @copyright (c) 2022 Jackson Miller
 */

#include "plan/TableItem.h"

namespace plan {

void to_json(nlohmann::json& json, const TableItem& product_target) {
	json["id"] = to_string(product_target.id_);
	json["item"] = product_target.target_item_;
}

TableItem::TableItem(const data::Item& target) :
		target_item_(target){
	id_ = uuids::uuid_system_generator{}();
}

TableItem::TableItem(uuids::uuid id, const data::Item& target):
		id_(id),
		target_item_(target) {
}

void TableItem::addProductLineReference(ProductLine* contributor) {
	associated_product_lines_.emplace_back(contributor);
}

bool TableItem::isAssociated(ProductLine* contributor) const {
	return std::any_of(associated_product_lines_.cbegin(),
					   associated_product_lines_.cend(),
					   [contributor](ProductLine* line) {
		return contributor == line;
	});
}

void TableItem::clearAssociated() {
	associated_product_lines_.clear();
}

} // namespace plan