#include <iostream>
#include <memory>

#define SDL_MAIN_HANDLED
#include "SDL/SDL.h"
#include "SDL_gfx/SDL2_gfxPrimitives.h"

#include "maths/vec.h"

#include "uni_util.hpp"
#include "uni_window.hpp"
#include "uni_render.hpp"

int main(int argc, char** argv) {
    int error_code = 0;
    std::unique_ptr<uni::Window> window;
    vec2i window_center;

    #ifdef DEBUG
        udbg << "Initializing...\n";
    #endif 
    if(SDL_Init(SDL_INIT_EVERYTHING)) {
        uerr << "Failed to initialize SDL...\n";
        uinf << SDL_GetError() << '\n';
        goto fail;
    }
    #ifdef DEBUG
        udbg << "Initalization success!\n";
    #endif

    #ifdef DEBUG
        unl; udbg << "Creating window...\n";
    #endif
    try {
        window = std::make_unique<uni::Window>(512, 512, "Testing...");
    } catch(uni::error e) {
        switch(e) {
        case uni::error::SDL_WINDOW_CREATION_ERROR: {
            uerr << "Failed to create SDL window...\n";
            uinf << SDL_GetError() << '\n';
        } break;
        case uni::error::SDL_RENDERER_CREATION_ERROR: {
            uerr << "Failed to create SDL renderer...\n";
            uinf << SDL_GetError() << '\n';
        } break;
        default:
            uerr << "Unknown error occurred while creating window...\n";
        }

        goto fail;
    }
    #ifdef DEBUG
        udbg << "Window creation success!\n";
    #endif

    window_center = vec2i(
        window->get_scl_width() / 2, window->get_scl_height() / 2
    );

    #ifdef DEBUG
        unl; udbg << "Entering main loop...\n";
    #endif
    while(true) {
        SDL_SetRenderDrawColor(window->render(), UNI_UNPACK_COLOR(0xFFDD33FF));
        SDL_RenderClear(window->render());
        
        uni::render_fill_rect(
            window->render(), window->map_rect(25, 50, 250, 250),
            0x2264FFFF
        );

        uni::circle test_circle = window->map_circle(250, 300, 100);
        filledCircleColor(
            window->render(), UNI_UNPACK_CIRCLE(test_circle),
            0xFF3300FF
        );

        uni::circle center = window->map_circle(
            window_center.x, window_center.y, 25
        );
        filledCircleColor(
            window->render(), UNI_UNPACK_CIRCLE(center),
            0x55B72FFF
        );

        SDL_Event event;
        while(SDL_PollEvent(&event)) switch(event.type) {
            case SDL_QUIT: goto close;
            case SDL_WINDOWEVENT: window->window_event(event); break;
        }

        SDL_RenderPresent(window->render());
    }

fail:
    error_code = -1;
close:
    #ifdef DEBUG
        unl; udbg << "Closing (code " << error_code << ")...\n";
    #endif
    return error_code;
}