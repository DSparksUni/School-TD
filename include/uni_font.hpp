#pragma once

#include <iostream>
#include <vector>

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

#include <uni_util.hpp>

namespace uni {
    class Font {
    private:
        using self = Font;
        
        TTF_Font* m_font;
        std::vector<SDL_Texture*> m_renders;

    public:
        Font(const char* path, size_t point_size);
        Font(const char*);
        ~Font();

        nodiscard TTF_Font* font() const noexcept;

        nodiscard SDL_Texture* render_u8(
            SDL_Renderer* render, const char* text, SDL_Color text_color
        ) noexcept;
    };
}
