#ifndef UNI_UTIL_HPP_INCLUDED_
#define UNI_UTIL_HPP_INCLUDED_

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

#include "maths/vec.h"

#define uerr std::cerr << "[ERROR] "
#define udbg std::cerr << "[DEBUG] "
#define uinf std::cerr << "[INFO] "
#define unl std::cerr << '\n'

#define nodiscard [[nodiscard]]

#define UNI_UNPACK_COLOR(c) (uint8_t)(c >> 24), (uint8_t)(c >> 16 & 0xFF), \
                            (uint8_t)(c >> 8 & 0xFF), (uint8_t)(c & 0xFF)
#define UNI_UNPACK_CIRCLE(c) c.x, c.y, c.r

namespace uni {
    enum error {
        SUCCESS = 0,
        SDL_WINDOW_CREATION_ERROR,
        SDL_WINDOW_SURFACE_CREATION_ERROR,
        SDL_RENDERER_CREATION_ERROR,
        ERROR_COUNT
    };

    struct circle {
        short int x, y, r;
    };

    double distance(double, double, double, double) noexcept;
    double distance(vec2d, vec2d) noexcept;
    double distance(vec2d, double, double) noexcept;
    double distance(double, double, vec2d) noexcept;
}

#endif  //UNI_U TIL_HPP_INCLUDED_
