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

    void addProductLine(const ProductLine& product_line);

	/**
	 * Adds given product to the subfactory's list of products
	 * @param target_product
	 */
    void addProduct(const std::shared_ptr<LineTarget>& target_product);

	/**
	 * Gives the difference between the product's target rate and what is produced by product lines on the table
	 * @param target
	 * @return
	 */
    [[nodiscard]] float productRemainder(const std::shared_ptr<LineTarget>& target) const;

	/**
	 * Total power draw for the subfactory
	 * @return
	 */
    [[nodiscard]] float powerDraw() const { return power_draw_; };

	/**
	 * Determines whether the given target is used by the product lines on the table
	 * @param item
	 * @return
	 */
    [[nodiscard]] bool isOnTable(const std::shared_ptr<LineTarget>& item) const;

	/**
	 * Creates a vector of line targets that omits targets used by the table\n
	 * Used to create "Ingredients" list
	 * @return
	 */
    [[nodiscard]] std::vector<std::shared_ptr<LineTarget>> ingredientsNotOnTable() const;

	void resetChangeability();

    void updateByproducts();
    void updateIngredients();
	void checkTargetCompletion();
    void calculate();
    void validate();

    std::vector<std::shared_ptr<LineTarget>> products_;
    std::vector<std::shared_ptr<LineTarget>> byproducts_;
    std::vector<std::shared_ptr<LineTarget>> ingredients_;
    std::vector<ProductLine> product_lines_;

  private:
    std::string label_;
    std::string icon_string_;

    float power_draw_ = 0.0;
};

using Subfactory_Ptr = std::shared_ptr<std::shared_ptr<Subfactory>>;

} // namespace plan

#endif //SATISFACTORY_PLANNER_SUBFACTORY_H
