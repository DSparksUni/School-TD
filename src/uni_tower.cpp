#include "uni_tower.hpp"

namespace uni {

    Bullet::Bullet(
        vec2i p, SDL_Rect* t, float s
    ) noexcept: pos(p), vel(vec2i::zero()), target(t), speed(s) {
        this->aim();
    }
    Bullet::Bullet(vec2i p, SDL_Rect* t) noexcept:
        self(p, t, self::DEFAULT_SPEED) {}
    Bullet::Bullet() noexcept:
        self(vec2i::zero(), nullptr) {}
    Bullet::Bullet(
        int px, int py, SDL_Rect* t, float s
    ) noexcept: self(vec2i{px, py}, t, s) {}
    Bullet::Bullet(int px, int py, SDL_Rect* t) noexcept:
        self(px, py, t, self::DEFAULT_SPEED) {}

    void Bullet::operator=(const Bullet& bullet) noexcept {
        this->pos = bullet.pos;
        this->target = bullet.target;

        this->aim();
    }

    void Bullet::aim() noexcept {
        this->vel = normalize(
            vec2f{this->target->x, this->target->y} -
            static_cast<vec2f>(this->pos)
        ) * this->speed;
    }

    nodiscard bool Bullet::hit_target() const noexcept {
        const auto t_max = vec2i {
            this->target->x + this->target->w,
            this->target->y + this->target->h
        };
        const auto m_max = vec2i {
            this->pos.x + this->width, this->pos.y + this->width
        };

        const auto check_right = this->target->x > m_max.x;
        const auto check_left = t_max.x < this->pos.x; 
        const auto check_up = this->target->y > m_max.y;
        const auto check_down = t_max.y < this->pos.y;

        return !(
            check_right || check_left || check_up || check_down
        );

        //return dist(this->pos, *this->target) <= self::TARGET_THRESHOLD;
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
            static_cast<vec2d>(this->vel) * dt
        );
    }

    Tower::Tower(SDL_Rect rect, const char* data_name):
        m_rect(rect), m_key_listener(KeyboardListener::get()),
        m_reload(0.0), m_target{0, 0, 0, 0}, m_reload_cycle(0.0),
        m_range(0.0) 
    {
        rapidjson::Document tower_data;
        tower_data.Parse(Json::get(data_name).c_str());

        assert(tower_data.HasMember("reload_cycle"));
        assert(tower_data["reload_cycle"].IsFloat());
        this->m_reload_cycle = tower_data["reload_cycle"].GetFloat();

        assert(tower_data.HasMember("range"));
        assert(tower_data["range"].IsFloat());
        this->m_range = tower_data["range"].GetFloat();
    }

    Tower::Tower(int x, int y, int w, int h, const char* data_name):
        self(SDL_Rect{x, y, w, h}, data_name) {}

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
            this->m_reload >= this->m_reload_cycle
        ) {
            this->shoot();
            this->m_reload = 0.0;
        } else this->m_reload += this->reload_mod * dt;

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
            this->m_rect.x + (this->m_rect.w/2),
            this->m_rect.y + (this->m_rect.h/2),
            &this->m_target
        );
    }

    void Tower::aim(const Enemy* enemy) noexcept {
        auto pos = enemy->pos();
        auto width = enemy->width();
        auto height = enemy->height();

        this->m_target = SDL_Rect {
            static_cast<int>(pos.x + (width/2)),
            static_cast<int>(pos.y + (height/2)),
            static_cast<int>(width), static_cast<int>(height)
        };
    }

    nodiscard SDL_Rect Tower::rect() const noexcept {
        return this->m_rect;
    }

    TestTower::TestTower(circle c):
        super{UNI_UNPACK_CIRCLE(c), c.r, "data/testtower_data.json"} {}
    TestTower::TestTower(int x, int y, int r):
        super{x, y, r, r, "data/testtower_data.json"} {}

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
