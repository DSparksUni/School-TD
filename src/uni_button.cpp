#include "uni_button.hpp"

namespace uni {
    Button::Button(SDL_Rect rect): m_border(rect), m_body(SDL_Rect{
        rect.x + 5, rect.y + 5, rect.w - 10, rect.h - 10
    }) {}
    Button::Button(int x, int y, int w, int h):
        Button(SDL_Rect{x, y, w, h}) {}

    nodiscard SDL_Rect Button::rect() const noexcept {
        return this->m_border;
    }
    nodiscard SDL_Rect Button::inner_rect() const noexcept {
        return this->m_body;
    }

    bool Button::click(vec2i mouse_pos) const noexcept {
        return (
            mouse_pos.x >= this->m_border.x &&
            mouse_pos.x <= this->m_border.x + this->m_border.w &&
            mouse_pos.y >= this->m_border.y &&
            mouse_pos.y <= this->m_border.y + this->m_border.y
        );
    }


    PrimitiveButton::PrimitiveButton(
        SDL_Rect rect, uint32_t border_color, uint32_t body_color
    ): super(rect), m_border_color(UNI_REVERSE_COLOR(border_color)),
       m_body_color(UNI_REVERSE_COLOR(body_color)) {}

    PrimitiveButton::PrimitiveButton(SDL_Rect rect):
        PrimitiveButton(rect, 0xFFFFFFFF, 0xFF00FFFF) {}

    PrimitiveButton::PrimitiveButton(
        int x, int y, int w, int h,
        uint32_t border_color, uint32_t body_color
    ): PrimitiveButton(SDL_Rect{x, y, w, h}, border_color, body_color) {}

    PrimitiveButton::PrimitiveButton(int x, int y, int w, int h):
        PrimitiveButton(SDL_Rect{x, y, w, h}) {}

    void PrimitiveButton::draw(
        std::unique_ptr<Window>& window
    ) const noexcept {
        SDL_Rect temp_rect;

        SDL_SetRenderDrawColor(
            window->render(), UNI_UNPACK_COLOR(this->m_border_color)
        );
        temp_rect = window->map_rect(this->m_border);
        SDL_RenderFillRect(window->render(), &temp_rect);

        SDL_SetRenderDrawColor(
            window->render(), UNI_UNPACK_COLOR(this->m_body_color)
        );
        temp_rect = window->map_rect(this->m_body);
        SDL_RenderFillRect(window->render(), &temp_rect);
    }


    ImageButton::ImageButton(
        SDL_Rect rect, SDL_Renderer* render, const char* img_path
    ): super(rect) {
        this->m_image = IMG_LoadTexture(render, img_path);
        if(!this->m_image) throw error::SDL_IMAGE_TEXTURE_CREATION_ERROR;
    }
    ImageButton::ImageButton(
        int x, int y, int w, int h, SDL_Renderer* render, const char* img_path
    ): ImageButton(SDL_Rect{x, y, w, h}, render, img_path) {}
    ImageButton::~ImageButton() {
        SDL_DestroyTexture(this->m_image);
    }

    void ImageButton::draw(std::unique_ptr<Window>& window) const noexcept {
        const SDL_Rect border_rect = window->map_rect(this->m_border);
        SDL_RenderCopy(window->render(), this->m_image, NULL, &border_rect);
    }
}
