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
    void addTarget(const std::shared_ptr<ProductTarget>& target_product);
    [[nodiscard]] float targetRemainder(const std::shared_ptr<ProductTarget>& target) const;
    [[nodiscard]] float powerDraw() const { return power_draw_; };
    [[nodiscard]] bool isTarget(const std::shared_ptr<ProductTarget>& item) const;
    [[nodiscard]] std::vector<std::shared_ptr<ProductTarget>> ingredientsNotOnTable() const;

    void updateByproducts();
    void updateIngredients();
    void calculate();
    void validate();

    std::vector<std::shared_ptr<ProductTarget>> targets_;
    std::vector<std::shared_ptr<ProductTarget>> byproducts_;
    std::vector<std::shared_ptr<ProductTarget>> ingredients_;
    std::vector<ProductLine> product_lines_;

  private:
    std::string label_;
    std::string icon_string_;

    float power_draw_ = 0.0;
};

using Subfactory_Ptr = std::shared_ptr<std::shared_ptr<Subfactory>>;

} // namespace plan

#endif //SATISFACTORY_PLANNER_SUBFACTORY_H
