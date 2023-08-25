#ifndef UNI_WINDOW_H_INCLUDED_
#define UNI_WINDOW_H_INCLUDED_

#include <stdio.h>

#include "SDL/SDL.h"

#include "uni_util.h"

typedef struct uni_window_t {
    size_t width, height;
    size_t scl_width, scl_height;

    SDL_Window* window;
    SDL_Renderer* render;
} uni_window;

uni_error uni_window_init(uni_window**, size_t, size_t, const char*);

size_t uni_window_map_to_width(uni_window*, size_t);
size_t uni_window_map_to_height(uni_window*, size_t);
size_t uni_window_intr_map(uni_window*, size_t);

void uni_window_handle_event(uni_window*, SDL_Event);

void uni_window_destroy(uni_window*);

#endif  //UNI_WINDOW_H_INCLUDED_