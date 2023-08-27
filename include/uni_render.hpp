#pragma once

#include <iostream>

#include "SDL/SDL.h"

#include "uni_util.hpp"

namespace uni {
    void render_draw_rect(SDL_Renderer*, SDL_Rect, uint32_t) noexcept;
    void render_fill_rect(SDL_Renderer*, SDL_Rect, uint32_t) noexcept;
}