#include "uni_enemy.hpp"

namespace uni {
    Enemy::Enemy(
        vec2i pos, const Level* path,
        const char* img_path, SDL_Renderer* render,
        float speed, uint32_t width, uint32_t height,
        uint32_t color
    ):  m_pos(static_cast<vec2f>(pos)), m_vel(vec2f::zero()),
        m_path(path), m_path_idx(-1), m_target(vec2i::zero()),
        m_last(vec2i::zero()), m_image(nullptr, nullptr), c_speed(speed),
        c_width(width), c_height(height), c_color(color)
    {
        auto image_raw = IMG_LoadTexture(render, img_path);
        if(!image_raw) throw error::SDL_IMAGE_TEXTURE_CREATION_ERROR;
        this->m_image = unique_texture(image_raw, uni::SDL_texture_deleter);

        this->advance();
    }
    Enemy::Enemy(
        int x, int y, const Level* path,
        const char* img_path, SDL_Renderer* render,
        float speed, uint32_t width, uint32_t height,
        uint32_t color
    ): Enemy(vec2i{x, y}, path, img_path, render, speed, width, height, color) {}

    Enemy::Enemy(
        vec2i pos, const Level* path, SDL_Renderer* render,
        const char* data_name
    ):  m_pos(static_cast<vec2f>(pos)), m_vel(vec2i::zero()),
        m_path(path), m_path_idx(-1), m_target(vec2i::zero()),
        m_last(vec2i::zero()), m_image(nullptr, nullptr)
    {
        rapidjson::Document enemy_data;
        enemy_data.Parse(Json::get(data_name).c_str());

        assert(enemy_data.HasMember("speed"));
        assert(enemy_data["speed"].IsFloat());
        this->c_speed = enemy_data["speed"].GetFloat();

        assert(enemy_data.HasMember("image"));
        assert(enemy_data["image"].IsString());
        std::string img_path = enemy_data["image"].GetString();
        auto img_raw = IMG_LoadTexture(render, img_path.c_str());
        if(!img_raw) throw error::SDL_IMAGE_TEXTURE_CREATION_ERROR;
        this->m_image = unique_texture(img_raw, uni::SDL_texture_deleter);

        assert(enemy_data.HasMember("width"));
        assert(enemy_data["width"].IsInt());
        this->c_width = enemy_data["width"].GetInt();

        assert(enemy_data.HasMember("height"));
        assert(enemy_data["height"].IsInt());
        this->c_height = enemy_data["height"].GetInt();

        assert(enemy_data.HasMember("color"));
        assert(enemy_data["color"].IsInt64());
        this->c_color = enemy_data["color"].GetInt64();

        assert(enemy_data.HasMember("health"));
        assert(enemy_data["health"].IsInt64());
        this->m_health = enemy_data["color"].GetInt64();

        this->advance();
    }   

    Enemy::Enemy(
        int x, int y, const Level* path, SDL_Renderer* render,
        const char* data_name
    ): self(vec2i{x, y}, path, render, data_name) {}

    void Enemy::set_direction() noexcept {
        this->m_vel = normalize(
            static_cast<vec2f>(this->m_target) -
            static_cast<vec2f>(this->m_last)
        ) * this->c_speed;
    }

    void Enemy::advance() noexcept {
        if(
            static_cast<size_t>(this->m_path_idx + 1) <
            this->m_path->len()
        ) this->m_path_idx++;
        this->m_last = this->m_path->get(this->m_path_idx);
        this->m_target = (
            static_cast<size_t>(this->m_path_idx + 1) <
            this->m_path->len()
        )? this->m_path->get(this->m_path_idx + 1) :
           vec2i(0, this->m_path->get(this->m_path->len() - 1).y);
        
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

    void Enemy::reset(vec2i pos) noexcept {
        this->m_pos = pos;
        this->m_path_idx = -1;
        this->advance();
    }

    void Enemy::draw(SDL_Renderer* render) const noexcept {
        SDL_Rect rect = {
            static_cast<uint32_t>(this->m_pos.x + 0.5f),
            static_cast<uint32_t>(this->m_pos.y + 0.5f),
            this->c_width, this->c_height
        };
        SDL_RenderCopy(render, this->m_image.get(), NULL, &rect);
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
        if(targ_dist <= this->c_speed * (this->c_speed + 1.f) * dt)
            this->advance();
    }


    Caterbug::Caterbug(
        vec2i pos, const Level* path, SDL_Renderer* render
    ): super(
        pos, path, render, "data/caterbug_data.json"
    ) {}
    Caterbug::Caterbug(
        int x, int y, const Level* path, SDL_Renderer* render
    ): self(vec2i{x, y}, path, render) {}
}
