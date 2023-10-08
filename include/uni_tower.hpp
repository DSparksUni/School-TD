#pragma once

#include <iostream>
#include <memory>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "uni_window.hpp"
#include "uni_util.hpp"

namespace uni {
    class Tower {
    private:
        using self = Tower;
    protected:
        SDL_Rect m_rect;

    public:
        Tower(SDL_Rect rect);
        Tower(int x, int y, int w, int h);
        virtual ~Tower() = default;

        virtual void draw(std::unique_ptr<Window>& window) const noexcept = 0;
        virtual void update(double dt) noexcept = 0;

        nodiscard SDL_Rect rect() const noexcept;
    };

    class TestTower : public Tower {
    private:
        using super = Tower;
        using self = TestTower;
    public:
        TestTower(circle c);
        TestTower(int x, int y, int r);
        virtual ~TestTower() = default;

        virtual void draw(
            std::unique_ptr<Window>& window
        ) const noexcept override;
        virtual void update(double dt) noexcept override;

        nodiscard circle get_circle() const noexcept;
    };
}
