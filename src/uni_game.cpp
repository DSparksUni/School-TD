#include "uni_game.hpp"

namespace uni {
    Game::Game(
        uint32_t window_width, uint32_t window_height, const char* window_title
    ) noexcept: m_window_width(window_width), m_window_height(window_height),
                m_window_title(window_title), m_time_now(0), m_time_last(0),
                window(nullptr), mouse_listener(nullptr), key_listener(nullptr),
                running(false), delta_time(0.0) {}

    nodiscard uni::error Game::init() noexcept {
        if(SDL_Init(SDL_INIT_EVERYTHING)) return error::SDL_INIT_ERROR;
        if(!IMG_Init(IMG_INIT_PNG)) return error::SDL_IMAGE_INIT_ERROR;
        if(TTF_Init()) return error::SDL_TTF_INIT_ERROR;

        try {
            this->window = std::make_unique<Window>(
                this->m_window_width, this->m_window_height,
                this->m_window_title
            );
        } catch(uni::error e) {
            return e;
        }

        this->key_listener = KeyboardListener::get();
        this->mouse_listener = MouseListener::get();

        this->m_time_last = 0;
        this->m_time_now = SDL_GetPerformanceCounter();
        
        this->running = true;

        return error::SUCCESS;
    }

    nodiscard uni::error Game::loop() noexcept {
        this->m_time_last = this->m_time_now;
        this->m_time_now = SDL_GetPerformanceCounter();
        this->delta_time = (double)(
            (double)(this->m_time_now - this->m_time_last) * 1000.0 /
            (double)SDL_GetPerformanceFrequency()
        ) * 0.05;

        this->mouse_listener->update();

        return error::SUCCESS;
    }

    void Game::destroy() noexcept {
    }

    nodiscard uni::error Game::run() noexcept {
        uni::error err = this->init();
        if(err) goto ret;

        while(this->running) {
            err = this->loop();
            if(err) goto ret;
        }

    ret:
        this->destroy();
        return err;
    }

    void quit() noexcept {
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
    }
}