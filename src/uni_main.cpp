#include <iostream>
#include <memory>

#define SDL_MAIN_HANDLED
#include "SDL/SDL.h"
#include "SDL_gfx/SDL2_gfxPrimitives.h"
#include "SDL/SDL_image.h"
#include "maths/vec.h"

#include "uni_util.hpp"
#include "uni_window.hpp"
#include "uni_render.hpp"

static constexpr uint32_t DEFAULT_WINDOW_HEIGHT = 512;
static constexpr uint32_t DEFAULT_WINDOW_WIDTH = DEFAULT_WINDOW_HEIGHT * 16 / 9;

int main(int argc, char** argv) {
    int error_code = 0;
    std::unique_ptr<uni::Window> window;
    SDL_Texture* test_lvl;

    #ifdef DEBUG
        udbg << "Initializing...\n";
    #endif 
    if(SDL_Init(SDL_INIT_EVERYTHING)) {
        uerr << "Failed to initialize SDL...\n";
        uinf << SDL_GetError() << '\n';
        goto fail;
    }

    if(!IMG_Init(IMG_INIT_PNG)) {
        uerr << "Failed to initialize SDL_image...\n";
        uinf << IMG_GetError() << '\n';
        goto fail;
    }
    #ifdef DEBUG
        udbg << "Initalization success!\n";
    #endif

    #ifdef DEBUG
        unl; udbg << "Creating window...\n";
    #endif
    try {
        window = std::make_unique<uni::Window>(
            DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, "Testing..."
        );
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

    if(argc < 2) {
        uerr << "Level data must be supplied...\n";
        goto fail;
    }
    test_lvl = IMG_LoadTexture(window->render(), argv[1]);
    if(!test_lvl) {
        uerr << "Failed to load texture from level image...\n";
        uinf << IMG_GetError() << '\n';
        goto fail;
    }

    #ifdef DEBUG
        unl; udbg << "Entering main loop...\n";
    #endif
    while(true) {
        SDL_SetRenderDrawColor(window->render(), UNI_UNPACK_COLOR(0xFFDD33FF));
        SDL_RenderClear(window->render());

        SDL_RenderCopy(window->render(), test_lvl, NULL, NULL);

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