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
	ProductLine(std::shared_ptr<data::Item> target, data::Recipe recipe);

    ProductLine& operator= (const ProductLine &rhs) { return *this; };

	void changeRecipe(const data::Recipe &recipe);
	void updateMultiplier(const float &target_per_min);

    [[nodiscard]] std::shared_ptr<data::Item> target() const { return target_; };
	[[nodiscard]] float targetOutput() const { return target_->rate(); };
	[[nodiscard]] float productOutput() const { return target_->rate() * percentage_; };
	[[nodiscard]] float multiplier() const { return multiplier_; };
	[[nodiscard]] data::Recipe recipe() const { return recipe_; };

	void setDone(bool done) { complete_ = done; };
	[[nodiscard]] bool isDone() const { return complete_; };
    [[nodiscard]] float calcPower() const;
    [[nodiscard]] float power() const { return power_; };
	[[nodiscard]] float clock() const { return clock_speed_ * 100; };
	void setClock(float clock_speed) { clock_speed_ = clock_speed / 100; };
	[[nodiscard]] float percent() const { return percentage_ * 100; };
	void setPercent(float percentage) { percentage_ = percentage / 100; };

    [[nodiscard]] std::vector<data::Item> calcIngredients() const;
    [[nodiscard]] std::vector<data::Item> ingredients() const { return ingredients_; };
    [[nodiscard]] std::vector<data::Item> calcProducts() const;
    [[nodiscard]] data::Item byproduct() const { return byproduct_.value(); };
    [[nodiscard]] bool hasByproduct() const { return byproduct_.has_value(); };

    void calculate();
    void update();
	void validate();
    [[nodiscard]] bool isValid() const { return valid_; };

	[[nodiscard]] float itemRateCalculation(int item_amount) const;
	[[nodiscard]] float multiplierCalculation(float target_rate, int target_item_amount) const;

  private:
    bool complete_ = false;
    std::shared_ptr<data::Item> target_;
	float percentage_ = 1.0;
	data::Recipe recipe_;
	float clock_speed_ = 1.0;
    float power_ = 0.0;
    std::optional<data::Item> byproduct_;
    std::vector<data::Item> ingredients_;

	float multiplier_;
    float timing_coefficient_ = 1.0;

    bool valid_ = false;

    void calcRate(data::Item& item) const;
};

} // namespace plan


#endif //SATISFACTORY_PLANNER_PRODUCTLINE_H
