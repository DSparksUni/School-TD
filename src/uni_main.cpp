#include <iostream>
#include <memory>

#define SDL_MAIN_HANDLED
#include "SDL/SDL.h"
#include "SDL_gfx/SDL2_gfxPrimitives.h"

#include "uni_util.hpp"
#include "uni_window.hpp"

int main(int argc, char** argv) {
    int error_code = 0;
    std::unique_ptr<uni::Window> window;

    udbg << "Initializing...\n";
    if(SDL_Init(SDL_INIT_EVERYTHING)) {
        uerr << "Failed to initialize SDL...\n";
        goto fail;
    }
    udbg << "Initalization success!\n";

    std::cerr << '\n';
    udbg << "Creating window...\n";
    try {
        window = std::make_unique<uni::Window>(512, 512, "Testing...");
    } catch(uni::error e) {
        switch(e) {
        case uni::error::SDL_WINDOW_CREATION_ERROR: {
            std::cout << "[ERROR] Failed to create SDL window...\n";
        } break;
        case uni::error::SDL_RENDERER_CREATION_ERROR: {
            std::cout << "[ERROR] Failed to create SDL renderer...\n";
        } break;
        default:
            std::cout << "[ERROR] Unknown error occurred while creating window...\n";
        }

        goto fail;
    }
    udbg << "Window creation success!\n";

    std::cerr << '\n';
    udbg << "Entering main loop...\n";
    while(true) {
        SDL_SetRenderDrawColor(window->render(), UNI_UNPACK_COLOR(0xFFDD33FF));
        SDL_RenderClear(window->render());
        
        SDL_Rect test_rect = window->map_rect(0, 0, 250, 250);
        SDL_SetRenderDrawColor(window->render(), UNI_UNPACK_COLOR(0x2264FFFF));
        SDL_RenderFillRect(window->render(), &test_rect);

        uni::circle test_circle = window->map_circle(250, 300, 100);
        filledCircleColor(
            window->render(), UNI_UNPACK_CIRCLE(test_circle),
            0xFF3300FF
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
    std::cerr << '\n';
    udbg << "Closing (code " << error_code << ")...\n";
    return error_code;
}