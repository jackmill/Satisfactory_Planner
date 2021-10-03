set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(${PROJECT_NAME}
        main.cpp
        MainWindow.cpp
        AboutDialog.cpp
        DataSourceDialog.cpp

        elements/BasicItemButton.cpp
        elements/ItemButton.cpp
        elements/ItemButtonLabel.cpp
        elements/ItemSelectionDialog.cpp
        elements/ItemSelectionIconGrid.cpp

        mainTable/FactoryTable.cpp

        subfactoryPane/SubfactoryPane.cpp
        subfactoryPane/SubfactoryInfo.cpp

        samples/TestButton.cpp
        )

include(FetchContent)
FetchContent_Declare(
        QSettingsContainer
        GIT_REPOSITORY "https://github.com/danielskeenan/QSettingsContainer.git"
        GIT_TAG        v1.0.0
)
FetchContent_MakeAvailable(QSettingsContainer)

target_link_libraries(${PROJECT_NAME} PUBLIC
        data
        plan
        Qt5::Widgets
        QSettingsContainer)