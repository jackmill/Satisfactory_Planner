set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_executable(${PROJECT_NAME}
        main.cpp
        MainWindow.h
        MainWindow.cpp
        AboutDialog.h
        AboutDialog.cpp)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(nlohmann_json REQUIRED)

target_link_libraries(${PROJECT_NAME}
        Qt5::Widgets
        nlohmann_json::nlohmann_json)