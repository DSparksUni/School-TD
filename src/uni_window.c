#include "uni_window.h"

uni_error uni_window_init(
    uni_window** out_window, size_t width, size_t height,
    const char* title
) {
    *out_window = NULL;

    uni_window* window = UNI_ALLOC(uni_window);
    if(!window) return UNI_ALLOC_ERROR;

    window->window = SDL_CreateWindow(
        title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        (int)width, (int)height, SDL_WINDOW_RESIZABLE
    );
    if(!window->window) return UNI_SDL_WINDOW_INIT_ERROR;

    window->render = SDL_CreateRenderer(
        window->window, -1, SDL_RENDERER_ACCELERATED
    );
    if(!window->render) return UNI_SDL_RENDERER_INIT_ERROR;

    window->width = window->scl_width = width;
    window->height = window->scl_height = height;

    *out_window = window;
    return UNI_SUCCESS;
}

size_t uni_map_to_value(size_t old_ceil, size_t new_ceil, size_t val) {
    return (size_t)(
        ((double)new_ceil / (double)old_ceil) * (double)val + 0.5
    );
}

size_t uni_window_map_to_width(uni_window* window, size_t x) {
    return uni_map_to_value(window->scl_width, window->width, x);
}

size_t uni_window_map_to_height(uni_window* window, size_t y) {
    return uni_map_to_value(window->scl_height, window->height, y);
}

size_t uni_window_intr_map(uni_window* window, size_t val) {
    return (size_t)((
        (double)uni_window_map_to_width(window, val) + 
        (double)uni_window_map_to_height(window, val)
    ) / 2.f + 0.5);
}

void uni_window_handle_event(uni_window* window, SDL_Event event) {
    switch(event.window.event) {
    case SDL_WINDOWEVENT_SIZE_CHANGED: {
        fputs("[DEBUG] Resizing window...\n", stderr);
        window->width = (size_t)event.window.data1;
        window->height = (size_t)event.window.data2;
        SDL_RenderPresent(window->render);
    } break;
    }
}

void uni_window_destroy(uni_window* window) {
    SDL_DestroyRenderer(window->render);
    SDL_DestroyWindow(window->window);
    free(window);
}