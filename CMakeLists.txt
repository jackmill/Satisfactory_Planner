cmake_minimum_required(VERSION 3.20)
project(Satisfactory_Planner
        VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(PROJECT_DISPLAY_NAME Satisfactory\ Planner)
list(APPEND CMAKE_MODULE_PATH ${PROJECT_BINARY_DIR})

add_subdirectory(src)