/**
 * @file Item.cpp
 * Created by jackm on 9/17/2021
 */

#include "data/Item.h"

namespace gameData {

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

}

int Item::amount() {
	if (amount_.has_value()) {
		return amount_.value();
	} else {
		return 0;
	}
}

void Item::setAmount(const int &amount) {
	amount_ = amount;
}

}

