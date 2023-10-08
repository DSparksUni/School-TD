#include "uni_font.hpp"

namespace uni {
    Font::Font(const char* path, size_t point_size) {
        this->m_font = TTF_OpenFont(path, point_size);
        if(!this->m_font) throw error::FONT_CREATION_ERROR;
    }
    Font::Font(const char* path): self(path, 50) {}
    Font::~Font() {
        for(SDL_Texture* texture : this->m_renders)
            SDL_DestroyTexture(texture);
        TTF_CloseFont(this->m_font);
    }

    nodiscard TTF_Font* Font::font() const noexcept {
        return this->m_font;
    }

    nodiscard SDL_Texture* Font::render_u8(
        SDL_Renderer* render, const char* text, SDL_Color text_color
    ) noexcept {
        SDL_Surface* render_surf = TTF_RenderUTF8_Solid(
            this->m_font, text, text_color
        );
        if(!render_surf) return NULL;

        SDL_Texture* render_text = SDL_CreateTextureFromSurface(
            render, render_surf
        );
        if(!render_text) goto ret;
        this->m_renders.push_back(render_text);

    ret:
        SDL_FreeSurface(render_surf);
        return render_text;
    }
}