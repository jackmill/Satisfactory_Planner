add_library(data
        Item.cpp
        Recipe.cpp
        Building.cpp
        Library.cpp
        )

find_package(nlohmann_json REQUIRED)


target_link_libraries(data nlohmann_json::nlohmann_json)