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
    void addTarget(const data::Item& target_product);
    float targetRemainder(const data::Item& target);

    void updateByproducts();
    void updateIngredients();

    std::vector<data::Item> product_targets_;
    std::vector<ProductLine> product_lines_;
    std::vector<data::Item> byproducts_;
    std::vector<data::Item> ingredients_;

  private:
    std::string label_;
    std::string icon_string_;


};

} // namespace plan

#endif //SATISFACTORY_PLANNER_SUBFACTORY_H
