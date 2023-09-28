#ifndef UNI_WINDOW_HPP_INCLUDED_
#define UNI_WINDOW_HPP_INCLUDED_

#include <iostream>

#include "SDL/SDL.h"

#include "uni_util.hpp"

namespace uni {
    class Window {
    private:
        uint32_t m_width, m_scl_width, m_height, m_scl_height;

        SDL_Window* m_window;
        SDL_Renderer* m_render;

        nodiscard uint32_t map_to_value(
            uint32_t old_ceil, uint32_t new_ceil, uint32_t val
        ) const noexcept;
    public:
        Window(uint32_t w, uint32_t h, const char* t);
        ~Window();

        nodiscard uint32_t width() const noexcept;
        nodiscard uint32_t scl_width() const noexcept;
        nodiscard uint32_t height() const noexcept;
        nodiscard uint32_t scl_height() const noexcept;

        nodiscard SDL_Window* window() const noexcept;
        nodiscard SDL_Surface* surface() const noexcept;
        nodiscard SDL_Renderer* render() const noexcept;

        nodiscard uint32_t map_to_width(uint32_t x) const noexcept;
        nodiscard uint32_t map_to_height(uint32_t y) const noexcept;
        nodiscard uint32_t intr_map(uint32_t v) const noexcept;
        nodiscard SDL_Rect map_rect(
            uint32_t x, uint32_t y, uint32_t w, uint32_t h
        ) const noexcept;
        nodiscard SDL_Rect map_rect(SDL_Rect rect) const noexcept;
        nodiscard circle map_circle(
            uint32_t x, uint32_t y, uint32_t r
        ) const noexcept;
        nodiscard circle map_circle(circle c) const noexcept;
        nodiscard vec2i map_point(vec2i point) const noexcept;
        nodiscard vec2i map_point(int x, int y) const noexcept;

        nodiscard vec2i backwards_map_point(vec2i point) const noexcept;
        nodiscard vec2i backwards_map_point(int x, int y) const noexcept;

        void window_event(SDL_Event e) noexcept;
    };
}

#endif  //UNI_WINDOW_HPP_INCLUDED_
