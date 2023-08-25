#ifndef UNI_RENDER_H_INCLUDED_
#define UNI_RENDER_H_INCLUDED_

#include <stdio.h>
#include <stdint.h>

#include "SDL/SDL.h"

#include "uni_util.h"

void uni_render_draw_bordered_rect(
    SDL_Renderer*, SDL_Rect*, uint8_t, uint8_t, uint8_t, uint8_t
);

#endif  //UNI_RENDER_H_INCLUDED_