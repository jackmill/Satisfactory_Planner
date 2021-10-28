/**
 * @project Satisfactory_Planner
 * @file Subfactory.cpp
 *
 * @author Jackson Miller
 * @date 2021-10-05
 * @copyright (c) 2021 Jackson Miller
 */

#include "plan/Subfactory.h"

namespace plan {

Subfactory::Subfactory(std::string label, std::string icon) :
    label_(std::move(label)),
    icon_string_(std::move(icon)) {
}

void Subfactory::addProductLine(ProductLine product_line) {
    product_lines_.emplace_back(std::move(product_line));
}

void Subfactory::addTarget(data::Item target_product) {
    product_targets_.emplace_back(std::move(target_product));
}

}