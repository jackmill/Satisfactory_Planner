/**
 * @file main.cpp
 * Created by jackm on 9/19/2021
 */

#include <iostream>

#include "data/Library.h"


int main() {
    std::cout << "Starting..." << std::endl;
    gameData::Library library = gameData::Library("resources/Docs 2.json");
    std::cout << "Done" << std::endl;

    return 0;
}