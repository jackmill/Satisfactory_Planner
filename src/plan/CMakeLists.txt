add_library(plan
        Factory.cpp
        Subfactory.cpp
        ProductLine.cpp)

target_link_libraries(plan data)