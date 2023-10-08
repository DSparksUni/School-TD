#pragma once

#include <iostream>
#include <memory>

#include "SDL/SDL.h"
#include "SDL_gfx/SDL2_gfxPrimitives.h"
#include "SDL/SDL_image.h"
#include "SDL_ttf/SDL_ttf.h"

#include "uni_util.hpp"
#include "uni_window.hpp"
#include "uni_mouse.hpp"
#include "uni_keyboard.hpp"
#include "uni_font.hpp"

namespace uni {
    class Game {
    private:
        using self = Game;

        uint32_t m_window_width;
        uint32_t m_window_height;
        const char* m_window_title;

        uint64_t m_time_now = SDL_GetPerformanceCounter();
        uint64_t m_time_last = 0;
    protected:
        std::unique_ptr<Window> window;
        std::shared_ptr<uni::MouseListener> mouse_listener;
        std::shared_ptr<uni::KeyboardListener> key_listener;
        bool running;
        double delta_time;

        nodiscard virtual uni::error init() noexcept;
        nodiscard virtual uni::error loop() noexcept;
        virtual void destroy() noexcept;
    
    public:
        Game(
            uint32_t window_width, uint32_t window_height,
            const char* window_title
        ) noexcept;
        virtual ~Game() = default;

        nodiscard uni::error run() noexcept;
    };
}