add_library(planner_data
        Item.cpp
        Recipe.cpp
        Building.cpp
        Library.cpp
        )

find_package(nlohmann_json REQUIRED)

target_link_libraries(planner_data nlohmann_json::nlohmann_json)