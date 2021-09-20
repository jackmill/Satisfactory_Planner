/**
 * @file Item.cpp
 * Created by jackm on 9/17/2021
 */

#include "data/Item.h"

namespace plannerData {

Item::Item(const std::string &recipe_str, const nlohmann::json &json) {
	std::string item_token = "ItemClass=";
	std::string amt_token = "Amount=";
	
	// Input looks like this:
	// ItemClass=BlueprintGeneratedClass'"/Game/FactoryGame/Resource/Parts/Non-FissibleUranium/Desc_NonFissibleUranium.Desc_NonFissibleUranium_C"',Amount=150
	
	std::string item_name = recipe_str.substr(recipe_str.find(item_token) + item_token.length(), recipe_str.find(',') - item_token.length());
	// BlueprintGeneratedClass'"/Game/FactoryGame/Resource/Parts/Non-FissibleUranium/Desc_NonFissibleUranium.Desc_NonFissibleUranium_C"'
	
	item_name = item_name.substr(item_name.find('.') + 1, item_name.find('\"', item_name.find('.')) - (item_name.find('.') + 1));
	// Desc_NonFissibleUranium_C
	
	for (auto native_class : json) {
		// Find FGItemDescriptor
		if (native_class.at("NativeClass") == "Class'/Script/FactoryGame.FGItemDescriptor'") {
			
			// Find "Desc_NonFissibleUranium_C"
			for (auto class_object : native_class.at("Classes")) {
				if (class_object.at("ClassName") == item_name) {
					
					// Set name_ to the given DisplayName
					name_ = class_object.at("mDisplayName");
				}
			}
		}
	}
	// Non-fissile Uranium
	
	// Amount=150
	amount_ = std::stoi(recipe_str.substr(recipe_str.find(amt_token) + amt_token.length()));
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

