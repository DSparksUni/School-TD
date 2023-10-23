#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "maths/vec.h"

#include "uni_window.hpp"
#include "uni_util.hpp"
#include "uni_mouse.hpp"

namespace uni {
    struct Bullet {
    private:
        using self = Bullet;
    
    public:
        vec2i pos, vel;
        const float speed;

        Bullet(vec2i p, vec2i v, float s) noexcept;
        Bullet(int px, int py, vec2i v, float s) noexcept;
        Bullet(vec2i p, int vx, int vy, float s) noexcept;
        Bullet(int px, int py, int vx, int vy, float s) noexcept;
        Bullet(vec2i p, vec2i v) noexcept;
        Bullet(int px, int py, vec2i v) noexcept;
        Bullet(vec2i p, int vx, int vy) noexcept;
        Bullet(int px, int py, int vx, int vy) noexcept;

        void draw(const Window* window) const noexcept;
        void update(double dt) noexcept;
    };

    class Tower {
    private:
        using self = Tower;
    protected:
        SDL_Rect m_rect;
        std::vector<Bullet> m_bullets;
        std::shared_ptr<MouseListener> m_mouse_listener;

    public:
        Tower(SDL_Rect rect);
        Tower(int x, int y, int w, int h);
        virtual ~Tower() = default;

        virtual void draw(const Window* window) const noexcept;
        virtual void update(double dt) noexcept;

        void shoot() noexcept;

        nodiscard SDL_Rect rect() const noexcept;
    };

    class TestTower : public Tower {
    private:
        using super = Tower;
        using self = TestTower;
    public:
        TestTower(circle c);
        TestTower(int x, int y, int r);
        virtual ~TestTower() = default;

        virtual void draw(
            const Window* window
        ) const noexcept override;
        virtual void update(double dt) noexcept override;

        nodiscard circle get_circle() const noexcept;
    };
}
