#include <iostream>
#include <memory>
#include <vector>

#define SDL_MAIN_HANDLED
#include "SDL/SDL.h"
#include "SDL_gfx/SDL2_gfxPrimitives.h"
#include "SDL/SDL_image.h"
#include "maths/vec.h"

#include "uni_util.hpp"
#include "uni_window.hpp"
#include "uni_render.hpp"
#include "uni_enemy.hpp"
#include "uni_button.hpp"
#include "uni_tower.hpp"
#include "uni_mouse.hpp"
#include "uni_keyboard.hpp"

static constexpr uint32_t DEFAULT_WINDOW_WIDTH = 910;
static constexpr uint32_t DEFAULT_WINDOW_HEIGHT = DEFAULT_WINDOW_WIDTH * 9 / 16;

int main(int argc, char** argv) {
    int error_code = 0;
    std::unique_ptr<uni::Window> window;
    SDL_Texture* test_lvl;
    uni::PrimitiveButton test_button(
        DEFAULT_WINDOW_WIDTH / 2 - 50, DEFAULT_WINDOW_HEIGHT / 2 - 25,
        100, 50
    );
    std::shared_ptr<uni::MouseListener> mouse_listener;
    std::shared_ptr<uni::KeyboardListener> key_listener;
    std::vector<vec2i> test_lvl_points;
    std::unique_ptr<uni::Enemy> test_enemy;
    std::unique_ptr<uni::TestTower> test_tower;
    uint64_t time_now = SDL_GetPerformanceCounter();
    uint64_t time_last = 0;
    double delta_time = 0.0;
    bool pause = false;
    bool pause_button = false;

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

    test_lvl_points = {
        {4, 93},    {27, 91},   {52, 91},
        {85, 91},   {112, 91},  {146, 95},
        {177, 97},  {207, 94},  {244, 93},
        {288, 91},  {330, 90},  {366, 87},
        {398, 93},  {440, 94},  {485, 94},
        {506, 95},  {545, 93},  {588, 89},
        {617, 80},  {642, 87},  {672, 103},
        {698, 117}, {712, 128}, {721, 143},
        {721, 158}, {720, 182}, {716, 219},
        {707, 243}, {700, 259}, {694, 293},
        {700, 325}, {711, 337}, {724, 351},
        {729, 373}, {731, 393}, {731, 416},
        {722, 431}, {693, 443}, {659, 445},
        {627, 442}, {597, 445}, {561, 444},
        {525, 444}, {507, 443}, {468, 441},
        {427, 437}, {379, 431}, {344, 428},
        {292, 425}, {250, 428}, {190, 428},
        {118, 417}, {68, 419},  {5, 415}
    };

    test_enemy = std::make_unique<uni::Enemy>(
        0, 93, test_lvl_points, "assets/bug-001.png", window->render()
    );

    test_tower = std::make_unique<uni::TestTower>(300, 256, 10);

    mouse_listener = uni::MouseListener::get();
    key_listener = uni::KeyboardListener::get();

    #ifdef DEBUG
        unl; udbg << "Entering main loop...\n";
    #endif
    while(true) {
        auto render_pause_alpha = [test_button](
            std::unique_ptr<uni::Window>& window
        ) {
            // Apply background fade
            SDL_SetRenderDrawColor(window->render(), 0xFF, 0xFF, 0xFF, 0xA5);
            SDL_SetRenderDrawBlendMode(window->render(), SDL_BLENDMODE_BLEND);
            SDL_Rect alpha_block = {
                0, 0, static_cast<int>(window->width()),
                static_cast<int>(window->height())
            };
            SDL_RenderFillRect(window->render(), &alpha_block);

            // Draw the unpause button
            test_button.draw(window);
        };

        // Calculate delta time
        time_last = time_now;
        time_now = SDL_GetPerformanceCounter();
        delta_time = (double)(
            (double)(time_now - time_last) * 1000. /
            (double)SDL_GetPerformanceFrequency()
        ) * 0.05;

        mouse_listener->update();
        
        SDL_SetRenderDrawColor(window->render(), UNI_UNPACK_COLOR(0xFFDD33FF));
        SDL_RenderClear(window->render());

        SDL_RenderCopy(window->render(), test_lvl, NULL, NULL);

        test_enemy->draw(window);
        test_tower->draw(window);

        if(pause) render_pause_alpha(window);

        // Process Events
        SDL_PumpEvents();
        SDL_Event event;
        while(SDL_PollEvent(&event)) switch(event.type) {
            case SDL_QUIT: goto close;
            case SDL_WINDOWEVENT: window->window_event(event); break;
        }

        // Handle keyboard input
        bool space_down = key_listener->key_down(SDL_SCANCODE_SPACE);
        if(space_down && !pause_button) {
            pause = !pause;
            pause_button = true;
        } else if(!space_down && pause_button) pause_button = false;

        if(mouse_listener->get_mouse_button(1) && pause) {
            if(test_button.click(
                window->backwards_map_point(mouse_listener->get_mouse_pos())
            )) pause = false;
        }
        
        // Update sprites and display
        if(!pause) {
            test_enemy->update(delta_time);
            test_tower->update(delta_time);
        }

        SDL_RenderPresent(window->render());
    }

fail:
    error_code = -1;
close:
    #ifdef DEBUG
        unl; udbg << "Closing (code " << error_code << ")...\n";
    #endif
    if(test_lvl) SDL_DestroyTexture(test_lvl);
    SDL_Quit(); IMG_Quit();
    return error_code;
}