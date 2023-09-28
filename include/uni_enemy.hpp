#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "maths/vec.h"

#include "uni_util.hpp"
#include "uni_window.hpp"

namespace uni {
    class Enemy {
    private:
        vec2f m_pos, m_vel;
        const std::vector<vec2i>& m_path;
        int m_path_idx;
        vec2i m_target;
        vec2i m_last;
        SDL_Texture* m_image;

        const float c_speed = 0.5f;
        const uint32_t c_width = 25;
        const uint32_t c_height = 25;
        const uint32_t c_color = 0xFFFF00FF;

        static constexpr double DISTANCE_THRESHOLD = 2.0;

        void set_direction() noexcept;
        void advance() noexcept;

    public:
        Enemy(
            vec2i pos, const std::vector<vec2i>& path,
            const char* img_path, SDL_Renderer* render
        );
        Enemy(
            int x, int y, const std::vector<vec2i>& path,
            const char* img_path, SDL_Renderer* render
        );
        ~Enemy();

        nodiscard vec2i pos() const noexcept;
        nodiscard float speed() const noexcept;
        nodiscard uint32_t width() const noexcept;
        nodiscard uint32_t height() const noexcept;

        void draw(std::unique_ptr<Window>& window) const noexcept;
        void update(double dt) noexcept;
    };
}