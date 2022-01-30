set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(QTCOMPONENTS Widgets)
find_package(Qt6 COMPONENTS ${QTCOMPONENTS} QUIET)
if(NOT Qt6_FOUND)
    find_package(Qt5 5.15 COMPONENTS ${QTCOMPONENTS} REQUIRED)
endif()

add_executable(${PROJECT_NAME}
        ${PROJECT_SOURCE_DIR}/resources/resources.qrc
        main.cpp
        MainWindow.cpp
        AboutDialog.cpp
        DataSourceDialog.cpp

        elements/ItemSelectionDialog.cpp
        elements/ItemListModel.cpp
        elements/TableIcon.cpp
        elements/BuildingTableIcon.cpp

        mainTable/ProductionPane.cpp
        mainTable/ProductionTableModel.cpp
        mainTable/SubfacItemListModel.cpp
        mainTable/ProductModel.cpp
        mainTable/SpinBoxDelegate.cpp
        mainTable/TableIconDelegate.cpp
        mainTable/IconListDelegate.cpp
        mainTable/IngredientIconList.cpp

        mainTable/RecipeSelectDialog/RecipeSelectDialog.cpp
        mainTable/RecipeSelectDialog/RecipeSelectModel.cpp
        mainTable/RecipeSelectDialog/RecipeIconList.cpp
        mainTable/RecipeSelectDialog/RecipeIconDelegate.cpp

        mainTable/PercentEditDialog/PercentEditDialog.cpp
        mainTable/ClockSpeedEditDialog/ClockSpeedEditDialog.cpp

        subfactoryPane/SubfactoryPane.cpp
        subfactoryPane/SubfactoryInfo.cpp
        subfactoryPane/SubfactoryListModel.cpp
        subfactoryPane/SubfactoryEditDialog.cpp
        subfactoryPane/IconListModel.cpp

        )

include(FetchContent)
FetchContent_Declare(
        QSettingsContainer
        GIT_REPOSITORY "https://github.com/danielskeenan/QSettingsContainer.git"
        GIT_TAG        v1.0.0
)
FetchContent_MakeAvailable(QSettingsContainer)

target_link_libraries(${PROJECT_NAME} PUBLIC
        plan
        Qt::Widgets
        QSettingsContainer)