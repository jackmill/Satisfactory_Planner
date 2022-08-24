/**
 * @project Satisfactory_Planner
 * @file TableItem.h
 * 
 * @author Jackson Miller
 * @date 2022-01-15
 * @copyright (c) 2022 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_TABLEITEM_H
#define SATISFACTORY_PLANNER_TABLEITEM_H

#include "uuid.h"
#include "data/Item.h"

namespace plan {

class ProductLine;

class TableItem {
	friend void to_json(nlohmann::json &json, const TableItem &product_target);

  public:
	explicit TableItem(const data::Item& target);
	TableItem(uuids::uuid id, const data::Item& target);

	[[nodiscard]] uuids::uuid id() const { return id_; }

	[[nodiscard]] data::Item target() const { return target_item_; }
	[[nodiscard]] std::string name() const { return target_item_.name(); }
	[[nodiscard]] std::string className() const { return target_item_.className(); }
	[[nodiscard]] float completion() const { return completion_; }
	void setCompletion(float comp) { completion_ = comp; }

	[[nodiscard]] int amount() const { return target_item_.amount(); }
	[[nodiscard]] float rate() const { return target_item_.rate(); }
	void setRate(const float& rate) { target_item_.setRate(rate); }
	void addRate(const float& rate) { target_item_.addRate(rate); }
	void clearAmount() { target_item_.clearAmount(); }

	void replaceWith(const data::Item& rhs) { target_item_.replaceWith(rhs); }

	[[nodiscard]] std::vector<ProductLine*> associatedProductLines() const { return associated_product_lines_; }
	void addProductLineReference(ProductLine* contributor);
	[[nodiscard]] bool isAssociated(ProductLine* contributor) const;
	void clearAssociated();

  private:
	uuids::uuid id_;
    data::Item target_item_;

	float completion_ = 0.0;

	std::vector<ProductLine*> associated_product_lines_;
};

} // namespace plan

#endif //SATISFACTORY_PLANNER_TABLEITEM_H
