#include "uni_window.hpp"

namespace uni {
    Window::Window(uint32_t w, uint32_t h, const char* t):
        m_width(w), m_scl_width(w), m_height(h), m_scl_height(h) {
            this->m_window = SDL_CreateWindow(
                t, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                w, h, SDL_WINDOW_RESIZABLE
            );
            if(!this->m_window) throw error::SDL_WINDOW_CREATION_ERROR;

            this->m_render = SDL_CreateRenderer(
                this->m_window, -1, SDL_RENDERER_ACCELERATED
            );
            if(!this->m_render) throw error::SDL_RENDERER_CREATION_ERROR;
    }

    Window::~Window() {
        SDL_DestroyRenderer(this->m_render);
        SDL_DestroyWindow(this->m_window);
    }

    nodiscard uint32_t Window::width() const noexcept {
        return this->m_width;
    }
    nodiscard uint32_t Window::scl_width() const noexcept {
        return this->m_scl_width;
    }
    nodiscard uint32_t Window::height() const noexcept {
        return this->m_height;
    }
    nodiscard uint32_t Window::scl_height() const noexcept {
        return this->m_scl_height;
    }

    nodiscard SDL_Window* Window::window() const noexcept {
        return this->m_window;
    }
    nodiscard SDL_Renderer* Window::render() const noexcept {
        return this->m_render;
    }

    nodiscard uint32_t Window::map_to_value(
        uint32_t old_ceil, uint32_t new_ceil, uint32_t val
    ) const noexcept {
        return (uint32_t)(
            ((double)new_ceil / (double)old_ceil) * (double)val + 0.5
        );
    }

    nodiscard uint32_t Window::map_to_width(uint32_t x) const noexcept {
        return this->map_to_value(this->m_scl_width, this->m_width, x);
    }

    nodiscard uint32_t Window::map_to_height(uint32_t y) const noexcept {
        return this->map_to_value(this->m_scl_height, this->m_height, y);
    }

    nodiscard uint32_t Window::intr_map(uint32_t v) const noexcept {
        return (uint32_t)((
            (double)this->map_to_width(v) + (double)this->map_to_height(v)
        ) / 2.f + 0.5);
    }

    nodiscard SDL_Rect Window::map_rect(
        uint32_t x, uint32_t y, uint32_t w, uint32_t h
    ) const noexcept {
        return SDL_Rect {
            static_cast<int>(this->map_to_width(x)),
            static_cast<int>(this->map_to_height(y)),
            static_cast<int>(this->map_to_width(w)),
            static_cast<int>(this->map_to_height(h))  
        };
    }

    nodiscard circle Window::map_circle(
        uint32_t x, uint32_t y, uint32_t r
    ) const noexcept {
        return circle {
            static_cast<short int>(this->map_to_width(x)),
            static_cast<short int>(this->map_to_height(y)),
            static_cast<short int>(this->intr_map(r))  
        };
    }

    void Window::window_event(SDL_Event e) noexcept {
        switch(e.window.event) {
        case SDL_WINDOWEVENT_SIZE_CHANGED: {
            this->m_width = e.window.data1;
            this->m_height = e.window.data2;
            SDL_RenderPresent(this->m_render);
        } break;
        }
    }
}