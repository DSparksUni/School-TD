#include "uni_render.hpp"

void render_rect(
    SDL_Renderer* render, SDL_Rect rect, uint32_t color, bool fill
) {
    SDL_SetRenderDrawColor(render, UNI_UNPACK_COLOR(color));
    
    if(fill) SDL_RenderFillRect(render, &rect);
    else SDL_RenderDrawRect(render, &rect);
}

namespace uni {
    void render_draw_rect(
        SDL_Renderer* render, SDL_Rect rect, uint32_t color
    ) noexcept {
        render_rect(render, rect, color, false);
    }

    void render_fill_rect(
        SDL_Renderer* render, SDL_Rect rect, uint32_t color
    ) noexcept {
        render_rect(render, rect, color, true);
    }
}