/**
 * @file main.cpp
 * Created by jackm on 9/19/2021
 */

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "nlohmann/json.hpp"

int main() {
	nlohmann::json json;
	std::ifstream file_in;
	file_in.open("resources/pretty.json");
	json = nlohmann::json::parse(file_in);
	file_in.close();
	
	std::string json_str = "((ItemClass=BlueprintGeneratedClass'\"/Game/FactoryGame/Resource/Parts/IronPlate/Desc_IronPlate.Desc_IronPlate_C\"',Amount=3),(ItemClass=BlueprintGeneratedClass'\"/Game/FactoryGame/Resource/Parts/Rubber/Desc_Rubber.Desc_Rubber_C\"',Amount=1))";
	
	// Remove enclosing parentheses
	json_str = json_str.substr(1, json_str.length() - 2);
	
	std::vector<std::string> ing_strs;
	std::string temp;
	for (auto character : json_str) {
//		std::cout << character << "\n" << temp << std::endl;
		if (character == '(' || character == ',') {
			continue;
		} else {
			if (character == ')') {
				ing_strs.push_back(temp);
				temp = "";
			} else {
				temp += character;
			}
		}
	}
	
	for (const auto &ingredient : ing_strs) {
		std::string item_token = "ItemClass=";
		std::string amt_token = "Amount=";
		
		/*
		// ItemClass=BlueprintGeneratedClass'"/Game/FactoryGame/Resource/Parts/Non-FissibleUranium/Desc_NonFissibleUranium.Desc_NonFissibleUranium_C"',Amount=150
		std::string item_name = ingredient.substr(ingredient.find(item_token) + item_token.length(),
		                                          ingredient.find(',') - item_token.length());
		*/
		// BlueprintGeneratedClass'"/Game/FactoryGame/Resource/Parts/Non-FissibleUranium/Desc_NonFissibleUranium.Desc_NonFissibleUranium_C"'
		std::string item_name = ingredient.substr(ingredient.find('.') + 1,
		                             ingredient.find('\"', ingredient.find('.')) - (ingredient.find('.') + 1));
		
		// Desc_NonFissibleUranium_C
		std::string display_name;
		
		for (auto native_class: json) {
			// Find FGItemDescriptor
			if (native_class.at("NativeClass") == "Class'/Script/FactoryGame.FGItemDescriptor'") {
				
				// Find "Desc_NonFissibleUranium_C"
				for (auto class_object: native_class.at("Classes")) {
					if (class_object.at("ClassName") == item_name) {
						
						// Set name_ to the given DisplayName
						display_name = class_object.at("mDisplayName");
					}
				}
			}
		}
		
		std::cout << display_name << std::endl;
		
		// Amount=150
		int amt = std::stoi(ingredient.substr(ingredient.find(amt_token) + amt_token.length()));
		std::cout << "Amount: " << amt << std::endl;
	}
}