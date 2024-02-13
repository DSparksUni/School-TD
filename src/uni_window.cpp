#include "uni_window.hpp"

namespace uni {
    Window::Window(uint32_t w, uint32_t h, const char* t):
        m_width(w), m_scl_width(1280), m_height(h), m_scl_height(720) {
            this->m_window = SDL_CreateWindow(
                t, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                w, h, SDL_WINDOW_RESIZABLE
            );
            if(!this->m_window) throw error::SDL_WINDOW_CREATION_ERROR;

            this->m_render = SDL_CreateRenderer(
                this->m_window, -1, SDL_RENDERER_ACCELERATED
            );
            if(!this->m_render) throw error::SDL_RENDERER_CREATION_ERROR;

            this->m_texture = SDL_CreateTexture(
                this->m_render,
                SDL_PIXELFORMAT_ARGB8888,
                SDL_TEXTUREACCESS_TARGET,
                1280, 720
            );
            if(!this->m_texture) throw error::SDL_TEXTURE_CREATION_ERROR;

            SDL_SetRenderTarget(this->m_render, this->m_texture);
    }

    Window::~Window() {
        SDL_DestroyTexture(this->m_texture);
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

    void Window::update() noexcept {
        SDL_SetRenderTarget(this->m_render, NULL);

        SDL_RenderCopyEx(
            this->m_render, this->m_texture, NULL, NULL,
            0.0, NULL, SDL_FLIP_NONE
        );
        SDL_RenderPresent(this->m_render);

        SDL_SetRenderTarget(this->m_render, this->m_texture);
    }

    nodiscard uint32_t Window::map_to_value(
        uint32_t old_ceil, uint32_t new_ceil, uint32_t val
    ) const noexcept {
        return (uint32_t)(
            ((double)new_ceil / (double)old_ceil) * (double)val + 0.5
        );
    }
#if false

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

    nodiscard SDL_Rect Window::map_rect(SDL_Rect rect) const noexcept {
        return this->map_rect(rect.x, rect.y, rect.w, rect.h);
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

    nodiscard circle Window::map_circle(circle c) const noexcept {
      return this->map_circle(UNI_UNPACK_CIRCLE(c));
    }

    nodiscard vec2i Window::map_point(vec2i point) const noexcept {
        return vec2i{
            static_cast<int>(this->map_to_width(point.x)),
            static_cast<int>(this->map_to_height(point.y))
        };
    }

    nodiscard vec2i Window::map_point(int x, int y) const noexcept {
        return this->map_point(vec2i{x, y});
    }
#endif
    nodiscard vec2i Window::backwards_map_point(vec2i point) const noexcept {
        return vec2i {
            this->map_to_value(
                this->m_width, this->m_scl_width,
                static_cast<uint32_t>(point.x)
            ),
            this->map_to_value(
                this->m_height, this->m_scl_height,
                static_cast<uint32_t>(point.y)
            )
        };
    }

    nodiscard vec2i Window::backwards_map_point(int x, int y) const noexcept {
        return this->backwards_map_point(vec2i{x, y});
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
