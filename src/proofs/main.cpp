/**
 * @file main.cpp
 * Created by jackm on 9/19/2021
 */

#include <iostream>

#include "data/Library.h"


int main() {
    std::cout << "Starting..." << std::endl;
    data::Library library = data::Library("resources/Docs.json");
    std::cout << "Done" << std::endl;

    return 0;
}