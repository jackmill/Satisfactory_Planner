/**
 * @project Satisfactory_Planner
 * @file Item.cpp
 *
 * @author Jackson Miller
 * @date 2021-09-17
 * @copyright (c) 2021 Jackson Miller
 */

#include "data/Item.h"

namespace data {

void to_json(nlohmann::json &json, const Item &item) {
    json["class_name"] = item.class_name_;
    json["amount"] = item.amount_.value_or(0);
    json["rate"] = item.rate_.value_or(0);
}

/**
 * Constructor for an item with no amount
 * @param class_name
 * @param db
 */
Item::Item(const std::string &class_name, const DBMap &db) :
    class_name_(class_name),
    name_(findKey(class_name, "mDisplayName", db)),
    is_liquid_(findKey(class_name, "mStackSize", db) == "SS_FLUID") {

    amount_.reset();
    rate_.reset();
}

/**
 * Constructor for an item with an amount
 * @return
 */
Item::Item(const std::string &class_name, const int &amount, const DBMap &db) :
    class_name_(class_name),
    name_(findKey(class_name, "mDisplayName", db)),
    is_liquid_(findKey(class_name, "mStackSize", db) == "SS_FLUID"),
    amount_(amount) {

    // The JSON DB lists liquid amounts multiplied by 1000, for some reason
    if (is_liquid_) {
        amount_.value() /= 1000;
    }

    rate_.reset();
}

int Item::amount() const {
	return amount_.value_or(0);
}

float Item::rate() const {
    return rate_.value_or(0);
}

void Item::setAmount(const int &amount) {
	amount_ = amount;
}

void Item::setRate(const float &rate) {
    rate_ = rate;
}

void Item::replaceWith(const Item &rhs) {
    name_ = rhs.name_;
    class_name_ = rhs.class_name_;
    is_liquid_ = rhs.is_liquid_;
    amount_ = rhs.amount_;
    rate_ = rhs.rate_;
}

}

