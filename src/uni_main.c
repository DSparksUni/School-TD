#include <stdio.h>
#include <stdbool.h>

#include "SDL/SDL.h"
#include "SDL_gfx/SDL2_gfxPrimitives.h"

#include "uni_window.h"
#include "uni_render.h"

#pragma GCC diagnostic ignored "-Wformat"
#pragma GCC diagnostic ignored "-Wformat-extra-args"

void clean(uni_window* window);

int main(int argc, char** argv) {
    int error_code = 0;

    fputs("[DEBUG] Initializing SDL...\n", stderr);
    if(SDL_Init(SDL_INIT_EVERYTHING)) {
        fputs("[ERROR] SDL initialization failure...\n", stderr);
        goto fail;
    }
    fputs("[DEBUG] Initlization success!\n", stderr);

    uni_window* window;
    fputs("[DEBUG] Creating window...\n", stderr);
    uni_error window_error = uni_window_init(&window, 512, 512, "Testing...");
    if(window_error) switch(window_error) {
        case UNI_ALLOC_ERROR: {
            fputs("[ERROR] Allocation failure...\n", stderr);
            goto fail;
        } break;
        case UNI_SDL_WINDOW_INIT_ERROR: {
            fputs("[ERROR] SDL window initialization failure...\n", stderr);
            fprintf(stderr, "[INFO] %s\n", SDL_GetError());
            goto fail;
        } break;
        case UNI_SDL_RENDERER_INIT_ERROR: {
            fputs("[ERROR] SDL renderer initialization failure...\n", stderr);
            fprintf(stderr, "[INOF] %s\n", SDL_GetError());
            goto fail;
        } break;
        default: fputs(
            "[ERROR] Unknown error while initializing window...\n",
            stderr
        ); goto fail;
    }
    fputs("[DEBUG] Window creation success!\n", stderr);

    fputs("[DEBUG] Entering main loop...\n", stderr);
    while(true) {
        SDL_SetRenderDrawColor(window->render, 255, 255, 0, 255);
        SDL_RenderClear(window->render);

        SDL_SetRenderDrawColor(window->render, 0, 0, 0, 255);
        uni_render_draw_bordered_rect(window->render, &(SDL_Rect){
                (int)uni_window_map_to_width(window, 100),
                (int)uni_window_map_to_height(window, 100),
                (int)uni_window_map_to_width(window, 250),
                (int)uni_window_map_to_height(window, 250)
        }, 255, 255, 255, 255);

        filledCircleRGBA(
            window->render,
            (short int)uni_window_map_to_width(window, 250),
            (short int)uni_window_map_to_height(window, 250),
            (short int)uni_window_intr_map(window, 50),
            0, 0, 255, 255
        );

        SDL_Event event;
        while(SDL_PollEvent(&event)) switch(event.type) {
            case SDL_QUIT: goto close;
            case SDL_WINDOWEVENT: {
                uni_window_handle_event(window, event);
            } break;
        }

        SDL_RenderPresent(window->render);
    }

close:
    fputs("[DEBUG] Closing...\n", stderr);
    clean(window);
    return error_code;
fail:
    error_code = -1;
    goto close;
}

void clean(uni_window* window) {
    uni_window_destroy(window);
    SDL_Quit();
}