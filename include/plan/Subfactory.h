/**
 * @project Satisfactory_Planner
 * @file Subfactory.h
 *
 * @author Jackson Miller
 * @date 2021-09-27
 * @copyright (c) 2021 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_SUBFACTORY_H
#define SATISFACTORY_PLANNER_SUBFACTORY_H

#include <string>
#include <vector>
#include <memory>

#include "ProductLine.h"
#include "data/Library.h"

namespace plan {

class Subfactory {
	friend void to_json(nlohmann::json &json, const Subfactory &subfactory);

  public:
	Subfactory() = default;
    Subfactory(std::string label, std::string icon);

    [[nodiscard]] std::string label() const { return label_; };
    [[nodiscard]] std::string icon() const { return icon_string_; };

    void setLabel(std::string label) { label_ = std::move(label); };
    void setIcon(std::string icon_string) { icon_string_ = std::move(icon_string); };

	[[nodiscard]] int numTargets() const { return static_cast<int>(targets_.size()); }
	[[nodiscard]] int numByproducts() const { return static_cast<int>(byproducts_.size()); }
	[[nodiscard]] int numIngredients() const { return static_cast<int>(ingredients_.size()); }
	[[nodiscard]] int numProductLines() const { return static_cast<int>(product_lines_.size()); }

	[[nodiscard]] bool hasTargets() const { return !targets_.empty(); }
	[[nodiscard]] bool hasByproducts() const { return !byproducts_.empty(); }
	[[nodiscard]] bool hasIngredients() const { return !ingredients_.empty(); }
	[[nodiscard]] bool hasProductLines() const { return !product_lines_.empty(); }

	[[nodiscard]] TableItem* targetAt(int pos) const { return targets_.at(pos).get(); }
	[[nodiscard]] data::Item byproductAt(int pos) const { return byproducts_.at(pos); }
	[[nodiscard]] TableItem* ingredientAt(int pos) const { return ingredients_.at(pos).get(); }
	[[nodiscard]] ProductLine* productLineAt(int pos) const { return product_lines_.at(pos).get(); }

    void addProductLine(const ProductLine& product_line);

	/**
	 * Adds given targetItem to the subfactory's list of targets\n
	 * If the given targetItem already exists, it will be combined
	 * @param target_product
	 */
    void addTarget(const TableItem& target_product);

	/**
	 * Adds given targetItem to the subfactory's list of targets\n
	 * If the given targetItem already exists, it will be combined
	 * @param target_product
	 */
	void addTarget(const data::Item& target_product);

	/**
	 * Add the given item's rate to the
	 * @param item
	 */
	void addToTarget(const data::Item& item);

	/**
	 * Removes target products between the given indices
	 * @param start_index
	 * @param end_index
	 */
	void removeTargets(int start_index, int end_index);

	/**
	 * Removes targetItem lines between the given indices
	 * @param start_index
	 * @param end_index
	 */
	void removeProductLines(int start_index, int end_index);

	/**
	 * Gives the difference between the product's target rate and what is produced by targetItem lines on the table
	 * @param target
	 * @return
	 */
    [[nodiscard]] float productRemainder(TableItem* target) const;

	/**
	 * Total power draw for the subfactory
	 * @return
	 */
    [[nodiscard]] float powerDraw() const;

	/**
	 * Checks if the given item is the target product of an existing targetItem line
	 * @param target
	 * @return
	 */
	[[nodiscard]] bool isOnTable(TableItem* target) const;

	/**
	 * Checks if the given item is a target
	 * @param target
	 * @return
	 */
	[[nodiscard]] bool isTarget(const data::Item& target) const;

	/**
	 * Checks if the given item is an intermediate product
	 * @param item
	 * @return
	 */
	[[nodiscard]] bool isIntermediate(const data::Item& item) const;

	/**
	 * Checks if the given item is an ingredient
	 * @param item
	 * @return
	 */
	[[nodiscard]] bool isIngredient(const data::Item& item) const;

	void checkTargetCompletion();
    void calculateTable();
	void calculate();
    void validate();

  private:
    std::string label_;
    std::string icon_string_;

	// Target products -- the 'goals' of this subfactory
	std::vector<std::unique_ptr<TableItem>> targets_;

	// Intermediary products
	// e.g. Steel Ingots in a Coal+Iron -> Steel Ingot -> Steel Pipe production line
	std::vector<std::unique_ptr<TableItem>> intermediates_;

	std::vector<std::unique_ptr<ProductLine>> product_lines_;

	std::vector<data::Item> byproducts_;
	std::vector<std::unique_ptr<TableItem>> ingredients_;
};

} // namespace plan

#endif //SATISFACTORY_PLANNER_SUBFACTORY_H
