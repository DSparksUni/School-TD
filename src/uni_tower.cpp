#include "uni_tower.hpp"

namespace uni {
    Bullet::Bullet(
        vec2i p, vec2i v, float s
    ) noexcept: pos(p), vel(v), speed(s) {}
    Bullet::Bullet(
        int px, int py, vec2i v, float s
    ) noexcept: pos{px, py}, vel(v), speed(s) {}
    Bullet::Bullet(
        vec2i p, int vx, int vy, float s
    ) noexcept: pos(p), vel{vx, vy}, speed(s) {}
    Bullet::Bullet(
        int px, int py, int vx, int vy, float s
    ) noexcept: pos{px, py}, vel{vx, vy}, speed(s) {} 
    Bullet::Bullet(vec2i p, vec2i v) noexcept: self(p, v, 6.f) {}
    Bullet::Bullet(int px, int py, vec2i v) noexcept: self(px, py, v, 6.f) {}
    Bullet::Bullet(vec2i p, int vx, int vy) noexcept: self(p, vx, vy, 6.f) {}
    Bullet::Bullet(
        int px, int py, int vx, int vy
    ) noexcept: self(px, py, vx, vy, 6.f) {}

    void Bullet::draw(const Window* window) const noexcept {
        const auto mapped = window->map_rect(this->pos.x, this->pos.y, 5, 5);
        SDL_SetRenderDrawColor(window->render(), UNI_UNPACK_COLOR(0xFF00DAFF));
        SDL_RenderDrawRect(window->render(), &mapped);
    }

    void Bullet::update(double dt) noexcept {
        this->pos += static_cast<vec2i>(
            static_cast<vec2d>(this->vel) * dt + 0.5
        );
    }

    Tower::Tower(SDL_Rect rect):
        m_rect(rect), m_mouse_listener(MouseListener::get()) {}
    Tower::Tower(int x, int y, int w, int h):
        m_rect{x, y, w, h}, m_mouse_listener(MouseListener::get()) {}

    void Tower::draw(const Window* window) const noexcept {
        for(const auto& bullet : this->m_bullets) bullet.draw(window);
    }

    void Tower::update(double dt) noexcept {
        if(this->m_mouse_listener->get_mouse_button(1)) this->shoot();

        for(auto& bullet : this->m_bullets) bullet.update(dt);
    }

    void Tower::shoot() noexcept {
        this->m_bullets.emplace_back(
            this->m_rect.x, this->m_rect.y, 0, 5
        );
    }

    nodiscard SDL_Rect Tower::rect() const noexcept {
        return this->m_rect;
    }

    TestTower::TestTower(circle c): super{UNI_UNPACK_CIRCLE(c), c.r} {}
    TestTower::TestTower(int x, int y, int r): super{x, y, r, r} {}

    void TestTower::draw(const Window* window) const noexcept {
        super::draw(window);

        circle mapped_circle = window->map_circle(
            this->m_rect.x, this->m_rect.y, this->m_rect.w
        );
        SDL_Rect mapped_rect = {
            UNI_UNPACK_CIRCLE(mapped_circle), mapped_circle.r
        };
    
        SDL_SetRenderDrawColor(window->render(), UNI_UNPACK_COLOR(0xFFFF00FF));
        SDL_RenderFillRect(window->render(), &mapped_rect);
    }

    void TestTower::update(double dt) noexcept {
        super::update(dt);
    }

    nodiscard circle TestTower::get_circle() const noexcept {
      return circle{
        static_cast<short>(this->m_rect.x),
        static_cast<short>(this->m_rect.y),
        static_cast<short>(this->m_rect.w)
      };
    }
}
