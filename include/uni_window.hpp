#ifndef UNI_WINDOW_HPP_INCLUDED_
#define UNI_WINDOW_HPP_INCLUDED_

#include <iostream>

#include "SDL/SDL.h"

#include "uni_util.hpp"

namespace uni {
    class Window {
    private:
        uint32_t width, scl_width, height, scl_height;

        SDL_Window* win;
        SDL_Renderer* renderer;
    
        nodiscard uint32_t map_to_value(
            uint32_t old_ceil, uint32_t new_ceil, uint32_t val
        ) const noexcept;
    public:
        Window(uint32_t w, uint32_t h, const char* t);
        ~Window();

        nodiscard uint32_t get_width() const noexcept;
        nodiscard uint32_t get_scl_width() const noexcept;
        nodiscard uint32_t get_height() const noexcept;
        nodiscard uint32_t get_scl_height() const noexcept;

        nodiscard SDL_Window* window() const noexcept;
        nodiscard SDL_Renderer* render() const noexcept;

        nodiscard uint32_t map_to_width(uint32_t x) const noexcept;
        nodiscard uint32_t map_to_height(uint32_t y) const noexcept;
        nodiscard uint32_t intr_map(uint32_t v) const noexcept;
        nodiscard SDL_Rect map_rect(
            uint32_t x, uint32_t y, uint32_t w, uint32_t h
        ) const noexcept;
        nodiscard circle map_circle(
            uint32_t x, uint32_t y, uint32_t r
        ) const noexcept;

        void window_event(SDL_Event e) noexcept;
    };
}

#endif  //UNI_WINDOW_HPP_INCLUDED_