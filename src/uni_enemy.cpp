#include "uni_enemy.hpp"

namespace uni {
    Enemy::Enemy(
        vec2i pos, const std::vector<vec2i>& path,
        const char* img_path, SDL_Renderer* render
    ):  m_pos(static_cast<vec2f>(pos)), m_vel(vec2f::zero()),
        m_path(path), m_path_idx(-1),
        m_target(vec2i::zero()), m_last(vec2i::zero())
    {
        this->m_image = IMG_LoadTexture(render, img_path);
        if(!this->m_image) throw error::SDL_IMAGE_TEXTURE_CREATION_ERROR;

        this->advance();
    }
    Enemy::Enemy(
        int x, int y, const std::vector<vec2i>& path,
        const char* img_path, SDL_Renderer* render
    ): Enemy(vec2i{x, y}, path, img_path, render) {}
    Enemy::~Enemy() {
        SDL_DestroyTexture(this->m_image);
    }

    void Enemy::set_direction() noexcept {
        this->m_vel = normalize((
            static_cast<vec2f>(this->m_target) -
            static_cast<vec2f>(this->m_last)
        )) * this->c_speed;
    }

    void Enemy::advance() noexcept {
        if(
            static_cast<size_t>(this->m_path_idx + 1) <
            this->m_path.size()
        ) this->m_path_idx++;
        this->m_last = this->m_path[this->m_path_idx];
        this->m_target = (
            static_cast<size_t>(this->m_path_idx + 1) <
            this->m_path.size()
        )? this->m_path[this->m_path_idx + 1] :
           vec2i(0, this->m_path[this->m_path.size() - 1].y);
        
        this->set_direction();
    }

    nodiscard vec2i Enemy::pos() const noexcept {
        return static_cast<vec2i>(this->m_pos + 0.5f);
    }
    nodiscard float Enemy::speed() const noexcept {
        return this->c_speed;
    }
    nodiscard uint32_t Enemy::width() const noexcept {
        return this->c_width;
    }
    nodiscard uint32_t Enemy::height() const noexcept {
        return this->c_height;
    }

    void Enemy::draw(std::unique_ptr<Window>& window) const noexcept {
        SDL_Rect rect = window->map_rect(
            static_cast<uint32_t>(this->m_pos.x + 0.5f),
            static_cast<uint32_t>(this->m_pos.y + 0.5f),
            this->c_width, this->c_height
        );
        SDL_RenderCopy(window->render(), this->m_image, NULL, &rect);
    }

    void Enemy::update(double dt) noexcept {
        this->set_direction();
        this->m_pos += static_cast<vec2f>(
            static_cast<vec2d>(this->m_vel) * dt
        );

        const double targ_dist = distance(
            static_cast<vec2d>(this->m_pos),
            static_cast<vec2d>(this->m_target)
        );
        if(targ_dist < this->DISTANCE_THRESHOLD * dt) this->advance();
    }
}