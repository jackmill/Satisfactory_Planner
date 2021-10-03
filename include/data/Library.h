/**
 * @file Library.h
 * Created by jackm on 9/19/2021
 */

#ifndef SATISFACTORY_PLANNER_LIBRARY_H
#define SATISFACTORY_PLANNER_LIBRARY_H

#include <string>
#include <vector>
#include <fstream>
#include "nlohmann/json.hpp"

#include "Recipe.h"

namespace data {

class Library {
  public:
	explicit Library() = default;
    explicit Library(const std::string &file_path);

    std::vector<Item> GetItems();
    std::vector<Recipe> FindRecipes(const Item &target_product);
    std::vector<Recipe> FindRecipes(const std::string &target_display_name);
	
	std::unordered_map<std::string, Item> items_;
	
  private:
    DBMap db_;
    std::unordered_map<std::string, Recipe> recipes_;
    
};

enum class Encoding {
    UTF8,
    UTF16LE,
    UTF16BE
};

Encoding guessEncoding(std::ifstream &file);
long getFilesize(std::ifstream &file);
std::vector<char> readUtf8(std::ifstream &file);
std::vector<uint16_t> readUtf16(std::ifstream &file, Encoding encoding);
nlohmann::json parse(std::ifstream &file);

}

#endif //SATISFACTORY_PLANNER_LIBRARY_H
