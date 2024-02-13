#include "uni_tower.hpp"

namespace uni {
    Bullet::Bullet(
        vec2i p, vec2i* t, float s
    ) noexcept: pos(p), target(t), speed(s) {
        if(this->target) this->aim();
    }
    Bullet::Bullet() noexcept:
        self(vec2i::zero(), nullptr, self::DEFAULT_SPEED) {}
    Bullet::Bullet(
        int px, int py, vec2i* t, float s
    ) noexcept: self(vec2i{px, py}, t, s) {}
    Bullet::Bullet(vec2i p, vec2i* t) noexcept:
        self(p, t, self::DEFAULT_SPEED) {}
    Bullet::Bullet(int px, int py, vec2i* t) noexcept:
        self(px, py, t, self::DEFAULT_SPEED) {}

    void Bullet::operator=(const Bullet& bullet) noexcept {
        this->pos = bullet.pos;
        this->target = bullet.target;
        if(this->target) this->aim();
    }

    void Bullet::aim() noexcept {
        this->vel = normalize(
            static_cast<vec2f>(*this->target) -
            static_cast<vec2f>(this->pos)
        ) * this->speed;
    }

    nodiscard bool Bullet::hit_target() const noexcept {
        return dist(this->pos, *this->target) <= self::TARGET_THRESHOLD;
    }

    void Bullet::draw(SDL_Renderer* render) const noexcept {
        const auto rect = SDL_Rect{
            this->pos.x, this->pos.y, this->width, this->width
        };
        SDL_SetRenderDrawColor(render, UNI_UNPACK_COLOR(0xFF00DAFF));
        SDL_RenderFillRect(render, &rect);
    }

    void Bullet::update(double dt) noexcept {
        this->aim();
        
        this->pos += static_cast<vec2i>(
            static_cast<vec2d>(this->vel) * dt + 0.5
        );
    }

    Tower::Tower(SDL_Rect rect):
        m_rect(rect), m_key_listener(KeyboardListener::get()),
        m_reload(0.0), m_target(vec2i::zero()) {}
    Tower::Tower(int x, int y, int w, int h):
        m_rect{x, y, w, h}, m_key_listener(KeyboardListener::get()),
        m_reload(0.0), m_target(vec2i::zero()) {}

    void Tower::draw(SDL_Renderer* render, Font* font) const noexcept {
        auto bullet_alive_text = font->render_u8(
            render, std::to_string(this->m_bullets.size()).c_str(),
            SDL_Color{0, 0, 0, 0xFF}
        ); 
        auto bullet_alive_rect = SDL_Rect{
            this->m_rect.x + 6, this->m_rect.y, this->m_rect.w - 10,
            this->m_rect.h
        };
        SDL_RenderCopy(
            render, bullet_alive_text, NULL, &bullet_alive_rect
        );

        for(const auto& bullet : this->m_bullets) bullet.draw(render);

        SDL_DestroyTexture(bullet_alive_text);
    }

    void Tower::update(const Window* window, double dt) noexcept {
        if(
            this->m_key_listener->key_down(SDL_SCANCODE_SPACE) &&
            this->m_reload >= this->reload_cycle
        ) {
            this->shoot();
            this->m_reload = 0.0;
        } else this->m_reload += reload_mod * dt;

        for(auto& bullet : this->m_bullets) bullet.update(dt);
        this->m_bullets.erase(std::remove_if(
            this->m_bullets.begin(), this->m_bullets.end(),
            [&window](const Bullet& bullet) {
                return  bullet.pos.y >= window->height()  ||
                        bullet.pos.y + bullet.width <= 0  ||
                        bullet.pos.x >= window->width()   ||
                        bullet.pos.x + bullet.width <= 0  ||
                        bullet.hit_target();
            }), this->m_bullets.end()
        );
    }

    void Tower::shoot() noexcept {
        this->m_bullets.emplace_back(
            this->m_rect.x + (this->m_rect.w / 2),
            this->m_rect.y + (this->m_rect.h / 2),
            &this->m_target
        );
    }

    void Tower::aim(const Enemy* enemy) noexcept {
        this->m_target = enemy->pos();
    }

    nodiscard SDL_Rect Tower::rect() const noexcept {
        return this->m_rect;
    }

    TestTower::TestTower(circle c): super{UNI_UNPACK_CIRCLE(c), c.r} {}
    TestTower::TestTower(int x, int y, int r): super{x, y, r, r} {}

    void TestTower::draw(SDL_Renderer* render, Font* font) const noexcept {
        SDL_Rect rect = {
            this->m_rect.x, this->m_rect.y, this->m_rect.w, this->m_rect.w
        };
    
        SDL_SetRenderDrawColor(render, UNI_UNPACK_COLOR(0xFFFF00FF));
        SDL_RenderFillRect(render, &rect);

        super::draw(render, font);
    }

    void TestTower::update(const Window* window, double dt) noexcept {
        super::update(window, dt);
    }

    nodiscard circle TestTower::get_circle() const noexcept {
      return circle{
        static_cast<short>(this->m_rect.x),
        static_cast<short>(this->m_rect.y),
        static_cast<short>(this->m_rect.w)
      };
    }
}
