/**
 * @project Satisfactory_Planner
 * @file Library.h
 *
 * @author Jackson Miller
 * @date 2021-09-19
 * @copyright (c) 2021 Jackson Miller
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
    explicit Library(const std::string &file_path, bool include_events);

    [[nodiscard]] Item findItem(const std::string &item_display_name) const { return items_.at(item_display_name); };

    [[nodiscard]] const DBMap& getDBMap() const { return db_; };

    [[nodiscard]] std::vector<Recipe> FindRecipes(const Item &target_product) const;
    [[nodiscard]] std::vector<Recipe> FindRecipes(const std::string &target_display_name) const;
    [[nodiscard]] const std::vector<Item> &getItemsSorted() const { return items_sorted_; }

  private:
    DBMap db_;
    std::unordered_map<std::string, Recipe> recipes_;
    std::unordered_map<std::string, Item> items_;
    std::vector<Item> items_sorted_;
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
