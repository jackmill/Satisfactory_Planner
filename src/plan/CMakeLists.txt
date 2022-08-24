add_library(plan
        Factory.cpp
        Subfactory.cpp
        ProductLine.cpp
        TableItem.cpp
        )

find_package(stduuid REQUIRED)

target_link_libraries(plan data stduuid::stduuid)