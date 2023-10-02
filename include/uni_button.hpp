#pragma once

#include <iostream>
#include <memory>
#include <string>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL_gfx/SDL2_imageFilter.h"
#include "maths/vec.h"
#include "maths/maths.h"

#include "uni_window.hpp"
#include "uni_util.hpp"

namespace uni {
    class Button {
    protected:
        SDL_Rect m_border;
        SDL_Rect m_body;

    public:
        Button(SDL_Rect rect);
        Button(int x, int y, int w, int h);
        virtual ~Button() = default;

        nodiscard SDL_Rect rect() const noexcept;
        nodiscard SDL_Rect inner_rect() const noexcept;

        virtual void draw(std::unique_ptr<Window>& window) const noexcept = 0;

        bool click(vec2i mouse_pos) const noexcept;
    };

    class PrimitiveButton : public Button {
    private:
        using super = Button;

        uint32_t m_border_color;
        uint32_t m_body_color;
    public:
        PrimitiveButton(
            SDL_Rect rect, uint32_t border_color, uint32_t body_color
        );
        PrimitiveButton(SDL_Rect rect);
        PrimitiveButton(
            int x, int y, int w, int h,
            uint32_t border_color, uint32_t body_color
        );
        PrimitiveButton(int x, int y, int w, int h);
        virtual ~PrimitiveButton() = default;

        virtual void draw(
            std::unique_ptr<Window>& window
        ) const noexcept override;
    };

    class ImageButton : public Button {
    private:
        using super = Button;

        SDL_Texture* m_image;

    public:
        ImageButton(SDL_Rect rect, SDL_Renderer* render, const char* img_path);
        ImageButton(
            int x, int y, int w, int h,
            SDL_Renderer* render, const char* img_path
        );
        virtual ~ImageButton();

        virtual void draw(
            std::unique_ptr<Window>& window
        ) const noexcept override;
    };
}