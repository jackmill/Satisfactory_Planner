/**
 * @project Satisfactory_Planner
 * @file Library.cpp
 *
 * @author Jackson Miller
 * @date 2021-09-19
 * @copyright (c) 2021 Jackson Miller
 */

#include <functional>
#include <iostream>
//#include <filesystem>

#include "data/Library.h"

namespace data {

Library::Library(const std::string &file_path, bool include_events) {
//     Open the file and make the json db
//    std::filesystem::path in_path(file_path);
//    if (!std::filesystem::is_regular_file(in_path)) {
//        throw (std::runtime_error("Can't read file"));
//    }

    std::ifstream file;
    file.exceptions(std::ifstream::badbit);
    file.open(file_path, std::ios_base::in | std::ios_base::binary);

    db_ = fromJson(parse(file));

    // Recipes
    for (const auto &recipe : db_.at("Class'/Script/FactoryGame.FGRecipe'")) {
        // Check for Event-ness, skip this recipe if it is
        std::string full_name = recipe.second.at("FullName");
        bool isEvent = full_name.find("/Events/") != std::string::npos;
        if (isEvent && !include_events) {
            continue;
        }

        Recipe temp_recipe = Recipe(recipe.first, db_);
        if (temp_recipe.isMachined()) {
            recipes_.emplace(temp_recipe.className(), temp_recipe);
        }
    }

    // Items
    for (const auto &recipe : recipes_) {
        std::vector<Item> recipe_products = recipe.second.productList();
        for (Item &product : recipe_products) {
            bool listed = false;
            for (const auto &item : items_) {
                if (product == item.second) {
                    listed = true;
                    break;
                }
            }

            if (!listed) {
                product.clearAmount();
                items_.emplace(product.name(), product);
                items_sorted_.emplace_back(product);
            }
        }
    }

    std::sort(items_sorted_.begin(), items_sorted_.end());
}

std::vector<Recipe> Library::FindRecipes(const Item &target_product) const {

    std::vector<Recipe> output_list;

    for (const auto &recipe : recipes_) {
        for (const auto &item : recipe.second.productList()) {
            if (target_product == item) {
                output_list.push_back(recipe.second);
            }
        }
    }

    return output_list;
}

std::vector<Recipe> Library::FindRecipes(const std::string &target_display_name) const {
    return FindRecipes(items_.at(target_display_name));
}


/**
 * Guess the encoding based on the byte-order mark (BOM) at the start of the file.\n\n
 *
 * Leaves the file cursor position after the BOM if it exists, or at the start
 * of the file if it does not.
 *
 * @param file
 * @return
 */
Encoding guessEncoding(std::ifstream &file) {
    // Always start at the beginning
    file.seekg(0);

    // Check first two bytes for UTF-16 byte-order mark
    std::array<unsigned char, 2> bom{0};
    file.read(reinterpret_cast<char*>(bom.data()), bom.size());
    if (bom[0] == 0xFF && bom[1] == 0xFE) {
        return Encoding::UTF16LE;
    } else if (bom[0] == 0xFE && bom[1] == 0xFF) {
        return Encoding::UTF16BE;
    }

    // Assume UTF-8 if not 16
    file.seekg(0);
    return Encoding::UTF8;
}

/**
 * Get the file's size without a filesystem query by getting the cursor position at the end.
 *
 * @param file
 * @return
 */
long getFilesize(std::ifstream &file) {
    // Save current position for later restoration.
    const auto old_pos = file.tellg();
    // Seek to the very end of the file.
    file.seekg(0, std::ifstream::end);
    // Where are we?
    const long filesize = file.tellg();
    // Restore.
    file.seekg(old_pos);

    return filesize;
}

std::vector<char> readUtf8(std::ifstream &file) {
    std::vector<char> result;
    result.reserve(getFilesize(file));
    while (!file.eof()) {
        // Read directly into the result.
        result.emplace_back(0);
        file.read(&result.back(), 1);
    }

    return result;
}

std::vector<uint16_t> readUtf16(std::ifstream &file, Encoding encoding) {
    // Create endian converters as needed.
    std::function<uint16_t(const std::array<char, 2> &)> endian_converter;
    if (encoding == Encoding::UTF16BE) {
        // CPU's endianness does not match encoding; flip the bytes.
        endian_converter = [](const std::array<char, 2> &new_char) {
            return (new_char[0] << 8) | new_char[1];
        };
    } else {
        endian_converter = [](const std::array<char, 2> &new_char) {
            // As written.
            return (new_char[1] << 8) | new_char[0];
        };
    }

    std::vector<uint16_t> result;
    result.reserve(getFilesize(file));
    while (!file.eof()) {
        // Zero-initialized buffer to read character into.
        std::array<char, 2> buf{0};
        file.read(buf.data(), buf.size());
        result.emplace_back(endian_converter(buf));
    }

    return result;
}

nlohmann::json parse(std::ifstream &file) {
    const auto encoding = guessEncoding(file);
    if (encoding == Encoding::UTF8) {
        const auto utf8_json = readUtf8(file);
        return nlohmann::json::parse(utf8_json.cbegin(), utf8_json.cend());
    } else {
        const auto utf16_json = readUtf16(file, encoding);
        return nlohmann::json::parse(utf16_json.cbegin(), utf16_json.cend());
    }
}

}