#pragma once

#include <iostream>
#include <memory>

#include "SDL/SDL.h"
#include "maths/vec.h"

#include "uni_util.hpp"

namespace uni {
    class MouseListener {
    public:
        void update() noexcept;
    private:
        using self = MouseListener;

        static std::shared_ptr<self> instance;
        static bool has_instance;

        uint32_t m_mouse_state;
        int m_mouse_x, m_mouse_y;

        MouseListener();

    public:
        static std::shared_ptr<self> get() noexcept;

        nodiscard int get_mouse_x() const noexcept;
        nodiscard int get_mouse_y() const noexcept;
        nodiscard vec2i get_mouse_pos() const noexcept;
        nodiscard bool get_mouse_button(int button) const noexcept;
    };
}