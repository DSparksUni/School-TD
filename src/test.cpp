#include <iostream>

#define SDL_MAIN_HANDLED
#include "SDL/SDL.h"

#include "uni_util.hpp"

int main(int argc, char** argv) {
    if(SDL_Init(SDL_INIT_EVERYTHING)) return -1;

    std::string enemy_data = uni::read_entire_file(argv[1]);

    std::cout << enemy_data;

    return 0;
}