#ifndef UNI_UTIL_HPP_INCLUDED_
#define UNI_UTIL_HPP_INCLUDED_

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <memory>

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "maths/vec.h"
#include "rapidjson/document.h"

#define uerr std::cerr << "[ERROR] "
#define uinf std::cerr << "[INFO] "
#define unl std::cerr << '\n'

#ifdef DEBUG
#define udbg std::cerr << "[DEBUG] "
#endif  

#define nodiscard [[nodiscard]]

#define UNI_UNPACK_COLOR(c) (uint8_t)(c >> 24), (uint8_t)(c >> 16 & 0xFF), \
                            (uint8_t)(c >> 8 & 0xFF), (uint8_t)(c & 0xFF)
#define __UNI_REVERSE_COLOR_IMPL(a, b, g, r) (r << 24) | (g << 16) | (b << 8) | a
#define __UNI_REVERSE_COLOR(c) __UNI_REVERSE_COLOR_IMPL(c)
#define UNI_REVERSE_COLOR(c) __UNI_REVERSE_COLOR(UNI_UNPACK_COLOR(c))
#define UNI_UNPACK_CIRCLE(c) c.x, c.y, c.r

namespace uni {
    using unique_texture = std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)>;

    enum error {
        SUCCESS = 0,
        SDL_INIT_ERROR,
        SDL_IMAGE_INIT_ERROR,
        SDL_TTF_INIT_ERROR,
        SDL_WINDOW_CREATION_ERROR,
        SDL_RENDERER_CREATION_ERROR,
        SDL_IMAGE_TEXTURE_CREATION_ERROR,
        FONT_CREATION_ERROR,
        FONT_RENDER_ERROR,    
        FILE_OPEN_ERROR,  
        ERROR_COUNT
    };

    struct circle {
        short int x, y, r;
    };

    struct KeySwitch {
    private:
        bool m_on;
        bool m_switch;
    
    public:
        KeySwitch() noexcept;

        nodiscard bool on() const noexcept;

        void turn_on() noexcept;
        void turn_off() noexcept;

        void activate(bool key) noexcept;
    };

    nodiscard std::string read_entire_file(const char* file_path);
    nodiscard rapidjson::Document read_json_data(const char* data_name);

    double distance(double, double, double, double) noexcept;
    double distance(vec2d, vec2d) noexcept;
    double distance(vec2d, double, double) noexcept;
    double distance(double, double, vec2d) noexcept;

    void SDL_texture_deleter(SDL_Texture*) noexcept;
}

#endif  //UNI_U TIL_HPP_INCLUDED_
