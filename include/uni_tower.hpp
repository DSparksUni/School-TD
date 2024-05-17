#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <sstream>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "maths/maths.h"
#include "maths/vec.h"
#include "rapidjson/document.h"

#include "uni_window.hpp"
#include "uni_util.hpp"
#include "uni_keyboard.hpp"
#include "uni_font.hpp"
#include "uni_enemy.hpp"

namespace uni {
    struct Bullet {
    private:
        using self = Bullet;
        static constexpr float DEFAULT_SPEED = 500.f;
        static constexpr float TARGET_THRESHOLD = 20.f;
    
    public:
        vec2i pos, vel;
        SDL_Rect* target;
        const float speed;
        const int width = 5;

        Bullet() noexcept;
        Bullet(vec2i p, SDL_Rect* t, float s) noexcept;
        Bullet(int px, int py, SDL_Rect* t, float s) noexcept;
        Bullet(vec2i p, SDL_Rect* t) noexcept;
        Bullet(int px, int py, SDL_Rect* t) noexcept;

        void operator=(const Bullet& bullet) noexcept;

        void aim() noexcept;
        nodiscard bool hit_target() const noexcept;

        void draw(SDL_Renderer* render) const noexcept;
        void update(double dt) noexcept;
    };

    class Tower {
    private:
        using self = Tower;
        //const double reload_cycle = 2.0;
        const double reload_mod = 25.0;
        //const double range = 300.0;

    protected:
        SDL_Rect m_rect;
        std::vector<Bullet> m_bullets;
        std::shared_ptr<KeyboardListener> m_key_listener;
        double m_reload;
        SDL_Rect m_target;

        double m_reload_cycle;
        double m_range;
        
    public:
        Tower(SDL_Rect rect, const char* data_name);
        Tower(int x, int y, int w, int h, const char* data_name);
        virtual ~Tower() = default;

        virtual void draw(SDL_Renderer* render, Font* font) const noexcept;
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
            SDL_Renderer* render, Font* font
        ) const noexcept override;
        virtual void update(const Window* window, double dt) noexcept override;

        nodiscard circle get_circle() const noexcept;
    };
}
