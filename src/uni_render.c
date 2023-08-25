#include "uni_render.h"

void uni_render_draw_bordered_rect(
    SDL_Renderer* render, SDL_Rect* rect,
    uint8_t br, uint8_t bg, uint8_t bb, uint8_t ba
) {
    SDL_RenderFillRect(render, rect);

    SDL_SetRenderDrawColor(render, br, bg, bb, ba);
    SDL_RenderDrawRect(render, rect);
}