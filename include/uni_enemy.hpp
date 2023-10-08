#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <cmath>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "maths/vec.h"

#include "uni_util.hpp"
#include "uni_window.hpp"

namespace uni {
    class Enemy {
    private:
        using self = Enemy;
    protected:
        vec2f m_pos, m_vel;
        const std::vector<vec2i>& m_path;
        int m_path_idx;
        vec2i m_target;
        vec2i m_last;
        SDL_Texture* m_image;

        const float c_speed;
        const uint32_t c_width;
        const uint32_t c_height;
        const uint32_t c_color;

        void set_direction() noexcept;
        void advance() noexcept;

        virtual double distance_threshold(double dt) const noexcept = 0;

    public:
        Enemy(
            vec2i pos, const std::vector<vec2i>& path,
            const char* img_path, SDL_Renderer* render,
            float speed, uint32_t width, uint32_t height,
            uint32_t color
        );
        Enemy(
            int x, int y, const std::vector<vec2i>& path,
            const char* img_path, SDL_Renderer* render,
            float speed, uint32_t width, uint32_t height,
            uint32_t color
        );
        virtual ~Enemy();

        nodiscard vec2i pos() const noexcept;
        nodiscard float speed() const noexcept;
        nodiscard uint32_t width() const noexcept;
        nodiscard uint32_t height() const noexcept;

        void reset(vec2i pos) noexcept;

        void draw(std::unique_ptr<Window>& window) const noexcept;
        void update(double dt) noexcept;
    };

    class Caterbug : public Enemy {
    private:
        using self = Caterbug;
        using super = Enemy;
    public:
        Caterbug(
            vec2i pos, const std::vector<vec2i>& path,
            SDL_Renderer* render
        );
        Caterbug(
            int x, int y, const std::vector<vec2i>& path,
            SDL_Renderer* render
        );
        virtual ~Caterbug() = default;
    
    protected:
        virtual double distance_threshold(double dt) const noexcept override;
    };
}