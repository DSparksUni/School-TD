#include <iostream>
#include <memory>
#include <vector>

#define SDL_MAIN_HANDLED
#include "SDL/SDL.h"
#include "SDL_gfx/SDL2_gfxPrimitives.h"
#include "SDL/SDL_image.h"
#include "SDL_ttf/SDL_ttf.h"
#include "maths/vec.h"

#include "uni_util.hpp"
#include "uni_window.hpp"
#include "uni_render.hpp"
#include "uni_enemy.hpp"
#include "uni_button.hpp"
#include "uni_tower.hpp"
#include "uni_mouse.hpp"
#include "uni_keyboard.hpp"
#include "uni_font.hpp"
#include "uni_game.hpp"

static constexpr uint32_t DEFAULT_WINDOW_WIDTH = 910;
static constexpr uint32_t DEFAULT_WINDOW_HEIGHT = DEFAULT_WINDOW_WIDTH * 9 / 16;

#ifdef DEBUG
static constexpr auto RESET_HOTKEY = SDL_SCANCODE_BACKSPACE;
static constexpr auto DEBUG_POINT_HOTKEY = SDL_SCANCODE_RETURN;
#endif

class SchoolTD : public uni::Game {
private:
    using self = SchoolTD;
    using super = uni::Game;

    std::vector<vec2i> test_lvl_points;
    SDL_Texture* test_lvl;
    uni::Font* monogram;
    SDL_Texture* pause_text;
    std::unique_ptr<uni::PrimitiveButton> test_button;
    uni::Enemy* test_enemy;
    std::unique_ptr<uni::Tower> test_tower;
    bool pause;
    bool pause_switch;

    #ifdef DEBUG
        bool reset;
        bool reset_switch;
        bool debug_point;
        bool debug_point_switch;
    #endif

    void draw_pause_screen() noexcept;
    void draw_debug_points() const noexcept;

    nodiscard virtual uni::error init() noexcept override;
    nodiscard virtual uni::error loop() noexcept override;
    virtual void destroy() noexcept override;
public:
    SchoolTD(
        uint32_t window_width, uint32_t window_height, const char* title
    ) noexcept;
    virtual ~SchoolTD() = default;
};

int main(int argc, char** argv) {
    SchoolTD game(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, "SchoolTD");
    uni::error runtime_error = game.run();
    if(!runtime_error) return 0;

    switch(runtime_error) {
    case uni::error::SDL_INIT_ERROR: {
        uerr << "Failed to initialize SDL...\n";
        uinf << SDL_GetError() << '\n';
    } break;
    case uni::error::SDL_IMAGE_INIT_ERROR: {
        uerr << "Failed to initialize SDL_image...\n";
        uinf << IMG_GetError() << '\n';
    } break;
    case uni::error::SDL_TTF_INIT_ERROR: {
        uerr << "Failed to intitialize SDL_ttf...\n";
        uinf << TTF_GetError() << '\n';
    } break;
    case uni::error::SDL_RENDERER_CREATION_ERROR: {
        uerr << "Failed to create SDL renderer...\n";
        uinf << SDL_GetError() << '\n';
    } break;
    case uni::error::SDL_WINDOW_CREATION_ERROR: {
        uerr << "Failed to create SDL window...\n";
        uinf << SDL_GetError() << '\n';
    } break;
    case uni::error::SDL_IMAGE_TEXTURE_CREATION_ERROR: {
        uerr << "Failed to create image texture...\n";
        uinf << SDL_GetError() << '\n';
    } break;
    case uni::error::FONT_CREATION_ERROR: {
        uerr << "Failed to create font...\n";
        uinf << TTF_GetError() << '\n';
    } break;
    case uni::error::FONT_RENDER_ERROR: {
        uerr << "Failed to render text with provided font...\n";
        uinf << TTF_GetError() << '\n';
    } break;
    default: uerr << "Unknown...\n";
    }

    return -1;
}

#ifdef DEBUG
SchoolTD::SchoolTD(
    uint32_t window_width, uint32_t window_height, const char* window_title
) noexcept: super(window_width, window_height, window_title), test_lvl(nullptr),
            monogram(nullptr), pause_text(nullptr), test_button(nullptr),
            test_enemy(nullptr), test_tower(nullptr), pause(false),
            pause_switch(false), reset(false), reset_switch(false),
            debug_point(false), debug_point_switch(false) {}
#else
SchoolTD::SchoolTD(
    uint32_t window_width, uint32_t window_height, const char* window_title
) noexcept: super(window_width, window_height, window_title), test_lvl(nullptr),
            monogram(nullptr), pause_text(nullptr), test_button(nullptr),
            test_enemy(nullptr), test_tower(nullptr), pause(false),
            pause_switch(false) {}
#endif

void SchoolTD::draw_pause_screen() noexcept {
    // Apply background fade
    SDL_SetRenderDrawColor(window->render(), 0xFF, 0xFF, 0xFF, 0x8A);
    SDL_SetRenderDrawBlendMode(window->render(), SDL_BLENDMODE_BLEND);
    SDL_Rect alpha_block = {
        0, 0, static_cast<int>(window->width()),
        static_cast<int>(window->height())
    };
    SDL_RenderFillRect(window->render(), &alpha_block);
            
    // Draw the unpause button
    test_button->draw(window);

    //Draw pause text
    SDL_SetRenderDrawBlendMode(window->render(), SDL_BLENDMODE_BLEND);
    const SDL_Rect button_inner = test_button->inner_rect();
    const SDL_Rect text_rect = window->map_rect(
        button_inner.x + 5, button_inner.y + 5,
        button_inner.w - 10, button_inner.h - 10
    );
    SDL_RenderCopy(window->render(), pause_text, NULL, &text_rect);
}

void SchoolTD::draw_debug_points() const noexcept {
    for(const vec2i point : test_lvl_points) {
        uni::circle point_circle = window->map_circle(
            point.x, point.y, 5
        );
        filledCircleColor(
            window->render(), UNI_UNPACK_CIRCLE(point_circle),
            0xFF3355BB
        );
    }
}

nodiscard uni::error SchoolTD::init() noexcept {
    uni::error super_init_error = super::init();
    if(super_init_error) return super_init_error;

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

    test_lvl = IMG_LoadTexture(window->render(), "assets/test_map.png");
    if(!test_lvl) return uni::error::SDL_IMAGE_TEXTURE_CREATION_ERROR;

    try {
        monogram = new uni::Font("assets/monogram.ttf");
    } catch(uni::error e) {
        return e;
    }

    pause_text = monogram->render_u8(
        window->render(), "Pause", SDL_Color{0, 0, 0, 255}
    );
    if(!pause_text) return uni::error::FONT_RENDER_ERROR;

    test_button = std::make_unique<uni::PrimitiveButton>(
        DEFAULT_WINDOW_WIDTH / 2 - 50, DEFAULT_WINDOW_HEIGHT / 2 - 25, 100, 50
    );

    test_enemy = new uni::Caterbug(0, 93, test_lvl_points, window->render());

    test_tower = std::make_unique<uni::TestTower>(300, 256, 30);

    return uni::error::SUCCESS;
}

nodiscard uni::error SchoolTD::loop() noexcept {
    uni::error super_loop_error = super::loop();
    if(super_loop_error) return super_loop_error;

    // Clear the display
    SDL_SetRenderDrawColor(window->render(), UNI_UNPACK_COLOR(0xFFDD33FF));
    SDL_RenderClear(window->render());

    // Render background
    SDL_RenderCopy(window->render(), test_lvl, NULL, NULL);

    // Draw sprites
    test_enemy->draw(window);
    test_tower->draw(window);

    #ifdef DEBUG
        if(debug_point) draw_debug_points();
    #endif
    if(pause) draw_pause_screen();

    // Event handling
    SDL_Event event;
    while(SDL_PollEvent(&event)) switch(event.type) {
        case SDL_QUIT: running = false; break;
        case SDL_WINDOWEVENT: window->window_event(event); break;
    }

    // Pause checking (keyboard)
    const bool space_down = key_listener->key_down(SDL_SCANCODE_SPACE);
    if(space_down && !pause_switch) {
        pause = !pause;
        pause_switch = true;
    } else if(!space_down && pause_switch) pause_switch = false;

    // Pause checking (button)
    if(mouse_listener->get_mouse_button(1) && pause) {
        if(test_button->click(
            window->backwards_map_point(mouse_listener->get_mouse_pos())
        )) pause = false;
    }

    // Debug switches
    #ifdef DEBUG
        // Reset (keyboard)
        const bool reset_button_down = key_listener->key_down(RESET_HOTKEY);
        if(reset_button_down && !reset_switch) {
            reset = !reset;
            reset_switch = true;
        } else if(!reset_button_down && reset_switch) reset_switch = false;

        // Debug points (keyboard)
        const bool debug_point_button_down = key_listener->key_down(
            DEBUG_POINT_HOTKEY
        );
        if(debug_point_button_down && !debug_point_switch) {
            debug_point = !debug_point;
            debug_point_switch = true;
        } else if(!debug_point_button_down && debug_point_switch)
            debug_point_switch = false;
    #endif

    // Reset handler
    if(reset) {
        reset = false;
        test_enemy->reset(vec2i{0, 93});
    }

    // Update sprites and display
    if(!pause) {
        test_enemy->update(delta_time);
        test_tower->update(delta_time);
    }

    SDL_RenderPresent(window->render());

    return uni::error::SUCCESS;
}

void SchoolTD::destroy() noexcept {
    if(test_lvl) SDL_DestroyTexture(test_lvl);
    if(monogram) delete monogram;
    if(test_enemy) delete test_enemy;
    super::destroy();
}
