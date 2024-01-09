#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "maths/vec.h"

#include "uni_window.hpp"
#include "uni_util.hpp"
#include "uni_keyboard.hpp"
#include "uni_font.hpp"
#include "uni_enemy.hpp"

namespace uni {
    struct Bullet {
    private:
        using self = Bullet;
        static constexpr float DEFAULT_SPEED = 6.f;
        static constexpr float TARGET_THRESHOLD = 5.f;
    
    public:
        vec2i pos, vel;
        vec2i* target;
        const float speed;
        const int width = 5;

        Bullet() noexcept;
        Bullet(vec2i p, vec2i* t, float s) noexcept;
        Bullet(int px, int py, vec2i* t, float s) noexcept;
        Bullet(vec2i p, vec2i* t) noexcept;
        Bullet(int px, int py, vec2i* t) noexcept;

        void operator=(const Bullet& bullet) noexcept;

        void aim() noexcept;
        nodiscard bool hit_target() const noexcept;

        void draw(const Window* window) const noexcept;
        void update(double dt) noexcept;
    };

    class Tower {
    private:
        using self = Tower;
        const double reload_cycle = 2.0;
        const double reload_mod = 0.25;
        const double range = 300.0;

    protected:
        SDL_Rect m_rect;
        std::vector<Bullet> m_bullets;
        std::shared_ptr<KeyboardListener> m_key_listener;
        double m_reload;
        vec2i m_target;
        
    public:
        Tower(SDL_Rect rect);
        Tower(int x, int y, int w, int h);
        virtual ~Tower() = default;

        virtual void draw(
            const Window* window, Font* font
        ) const noexcept;
        virtual void update(const Window* window, double dt) noexcept;

        void shoot() noexcept;
        void aim(const Enemy* enemy) noexcept;

        nodiscard SDL_Rect rect() const noexcept;
    };

    class TestTower : public Tower {
    private:
        using super = Tower;
        using self = TestTower;
    public:
        TestTower(circle c);
        TestTower(int x, int y, int r);

        virtual void draw(
            const Window* window, Font* font
        ) const noexcept override;
        virtual void update(const Window* window, double dt) noexcept override;

        nodiscard circle get_circle() const noexcept;
    };
}
