/**
 * @project Satisfactory_Planner
 * @file ProductLine.h
 *
 * @author Jackson Miller
 * @date 2021-10-02
 * @copyright (c) 2021 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_PRODUCTLINE_H
#define SATISFACTORY_PLANNER_PRODUCTLINE_H

#include <vector>

#include "data/Recipe.h"

namespace plan {

class ProductLine {
    friend void to_json(nlohmann::json &json, const ProductLine &product_line);

  public:
	ProductLine(data::Item& target, const data::Recipe& recipe);

    ProductLine& operator= (const ProductLine &rhs) { return *this; };

	void changeRecipe(const data::Recipe &recipe);
	void updateMultiplier(const float &target_per_min);

    [[nodiscard]] data::Item target() const { return target_; };
	[[nodiscard]] float targetOutput() const { return target_.rate(); };
	[[nodiscard]] float multiplier() const { return multiplier_; };
	[[nodiscard]] data::Recipe recipe() const { return recipe_; };

    [[nodiscard]] float calcPower() const;
    [[nodiscard]] std::vector<data::Item> calcIngredients() const;
    [[nodiscard]] std::vector<data::Item> calcProducts() const;

    void setDone(bool done) { complete_ = done; };
    [[nodiscard]] bool isDone() const { return complete_; };

  private:
	data::Item& target_;
	data::Recipe recipe_;
	float multiplier_;
    float timing_coefficient_;

    bool complete_ = false;
};

} // namespace plan


#endif //SATISFACTORY_PLANNER_PRODUCTLINE_H
