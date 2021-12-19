/**
 * @project Satisfactory_Planner
 * @file main.cpp
 *
 * @author Jackson Miller
 * @date 2021-09-19
 * @copyright (c) 2021 Jackson Miller
 */

#include <iostream>

#include "data/Library.h"


int main() {
    std::cout << "Starting..." << std::endl;
    data::Library library = data::Library("resources/Docs.json");
    std::cout << "Done" << std::endl;

    return 0;
}