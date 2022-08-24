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
#include "plan/TableItem.h"

namespace plan {

class ProductLine {
    friend void to_json(nlohmann::json &json, const ProductLine &product_line);

  public:
	ProductLine(TableItem* target, data::Recipe recipe);

    ProductLine& operator= (const ProductLine &rhs) { return *this; };

	void changeRecipe(const data::Recipe &recipe);
	void updateMultiplier(const float &target_per_min);

    [[nodiscard]] uuids::uuid id() const { return id_; }
	[[nodiscard]] TableItem* target() const { return target_; }
	[[nodiscard]] data::Item targetItem() const { return target_->target(); }
	[[nodiscard]] float targetRate() const { return target_->rate(); }
	[[nodiscard]] float actualOutputRate() const { return target_->rate() * percentage_; }
	[[nodiscard]] float multiplier() const { return multiplier_; }
	[[nodiscard]] data::Recipe recipe() const { return recipe_; }

	void setDone(bool b) { marked_complete_ = b; }
	[[nodiscard]] bool isMarkedComplete() const { return marked_complete_; }
    [[nodiscard]] float calcPower() const;
    [[nodiscard]] float power() const { return power_; }
	[[nodiscard]] float clockSpeed() const { return clock_speed_ * 100; }
	void setClockSpeed(float d) { clock_speed_ = d / 100; }
	[[nodiscard]] float percent() const { return percentage_ * 100; }
	void setPercent(float d) { percentage_ = d / 100; }

    [[nodiscard]] std::vector<data::Item> calcIngredients() const;
    [[nodiscard]] std::vector<data::Item> ingredients() const { return ingredients_; }
    [[nodiscard]] std::vector<data::Item> calcProducts() const;
    [[nodiscard]] data::Item byproduct() const { return byproduct_.value(); }
    [[nodiscard]] bool hasByproduct() const { return byproduct_.has_value(); }
	[[nodiscard]] bool useByproduct() const { return use_byproduct_; }
	void setUseByproduct(bool b) { use_byproduct_ = b; }
	[[nodiscard]] bool isChangeable() const { return is_changeable_; }
	void setChangeable(bool b) { is_changeable_ = b; }

    void calculate();
    void update();
	void validate();
    [[nodiscard]] bool isValid() const { return valid_; }

	[[nodiscard]] float itemRateCalculation(int item_amount) const;
	[[nodiscard]] float multiplierCalculation(float target_rate, int target_item_amount) const;

  private:
    uuids::uuid id_;
	bool marked_complete_ = false;
    TableItem* target_;
	float percentage_ = 1.0;
	data::Recipe recipe_;
	float clock_speed_ = 1.0;
    float power_ = 0.0;
    std::optional<data::Item> byproduct_;
    std::vector<data::Item> ingredients_;

	float multiplier_;
    float timing_coefficient_ = 1.0;

    bool valid_ = false;
	bool use_byproduct_ = true;
	bool is_changeable_ = true;
};

} // namespace plan


#endif //SATISFACTORY_PLANNER_PRODUCTLINE_H
