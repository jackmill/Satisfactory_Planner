/**
 * @file Item.cpp
 * Created by jackm on 9/17/2021
 */

#include "data/Item.h"

namespace plannerData {

Item::Item(std::string name) : name_(std::move(name)) {}

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

