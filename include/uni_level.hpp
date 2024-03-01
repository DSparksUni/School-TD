#pragma once

#include <iostream>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "maths/vec.h"

#include "uni_util.hpp"

namespace uni {
    class Level {
    private:
        using self = Level;

    protected:
        SDL_Texture* m_image;
        std::vector<vec2i> m_path;

    public:
        Level(
            SDL_Renderer* render, const char* image_path,
            std::vector<vec2i> path
        );
        ~Level();

        nodiscard SDL_Texture* image() const noexcept;
        nodiscard const std::vector<vec2i>& path() const noexcept;

        nodiscard vec2i get(size_t index) const noexcept;
        nodiscard vec2i operator[](size_t index) const noexcept;

        nodiscard size_t len() const noexcept; 
        
        void draw(SDL_Renderer* render) const noexcept;
    };

    class TestLevel : public Level {
    private:
        using self = TestLevel;
        using super = Level;

    public:
        TestLevel(SDL_Renderer* render);
    };
}
