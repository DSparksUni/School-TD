#ifndef UNI_UTIL_HPP_INCLUDED_
#define UNI_UTIL_HPP_INCLUDED_

#include <iostream>

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
        SDL_RENDERER_CREATION_ERROR,
        ERROR_COUNT
    };

    struct circle {
        short int x, y, r;
    };
}

#endif  //UNI_UTIL_HPP_INCLUDED_
