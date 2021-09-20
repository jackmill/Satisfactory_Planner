cmake_minimum_required(VERSION 3.20)
project(Satisfactory_Planner
        VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(PROJECT_DISPLAY_NAME Satisfactory\ Planner)
set(PROJECT_ORGANIZATION_NAME "jackmill")
set(PROJECT_ORGANIZATION_DOMAIN "github.com/jackmill")
list(APPEND CMAKE_MODULE_PATH ${PROJECT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src)