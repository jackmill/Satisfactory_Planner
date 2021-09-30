//
// Created by Jackson Miller on 9/24/21.
//

#ifndef SATISFACTORY_PLANNER_DBMAP_H
#define SATISFACTORY_PLANNER_DBMAP_H

#include <string>
#include <unordered_map>
#include "nlohmann/json.hpp"

namespace gameData {

using DocsObject = std::unordered_map<std::string, nlohmann::json>;
using DBMap = std::unordered_map<std::string, DocsObject>;

/**
 * Docs.json is an array of objects that are themselves a key (NativeClass) and an array (Classes)\n\n
 * This breaks up the json file into a series of maps of maps, keyed by either their NativeClass name or the ClassName of the underlying array object
 * @param json_db
 * @return
 */
inline DBMap fromJson(const nlohmann::json &json_db) {
    DBMap db;

    //
    for (const auto &native_class : json_db) {
        DocsObject top_level_object;
        for (const auto &class_object : native_class.at("Classes")) {
            top_level_object.emplace(class_object.at("ClassName"), class_object);
        }
        db.emplace(native_class.at("NativeClass"), top_level_object);
    }

    return db;
}

/**
 * Find the mDisplayName that corresponds with a given ClassName\n
 * e.g. Recipe_Alternate_FusedWire_C -> Alternate: Fused Wire
 * @param class_name
 * @param db
 * @return
 */
inline std::string findKey(const std::string &class_name, const std::string &key, const DBMap &db) {
    std::string found;
    for (const auto &object : db) {
        if (object.second.count(class_name)) {
            found = object.second.at(class_name).at(key);
        }
    }
    return found;
}

} // namespace gameData

#endif //SATISFACTORY_PLANNER_DBMAP_H
