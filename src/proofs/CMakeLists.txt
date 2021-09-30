add_executable(proofs_cli main.cpp)

find_package(nlohmann_json REQUIRED)

target_link_libraries(proofs_cli nlohmann_json::nlohmann_json planner_data)