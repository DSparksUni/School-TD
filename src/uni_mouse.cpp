#include "uni_mouse.hpp"

namespace uni {
    bool MouseListener::has_instance = false;
    std::shared_ptr<MouseListener> MouseListener::instance = nullptr;

    void MouseListener::update() noexcept {
        this->m_mouse_state = SDL_GetMouseState(
            &this->m_mouse_x, &this->m_mouse_y
        );
    }

    MouseListener::MouseListener() {
        this->update();
    }

    std::shared_ptr<MouseListener> MouseListener::get() noexcept {
        if(!has_instance) {
            instance = std::shared_ptr<MouseListener>(new MouseListener());
            has_instance = true;
        }

        return instance;
    }

    nodiscard int MouseListener::get_mouse_x() const noexcept {
        return this->m_mouse_x;
    }
    nodiscard int MouseListener::get_mouse_y() const noexcept {
        return this->m_mouse_y;
    }
    nodiscard vec2i MouseListener::get_mouse_pos() const noexcept {
        return vec2i{this->m_mouse_x, this->m_mouse_y};
    }
    nodiscard bool MouseListener::get_mouse_button(int button) const noexcept {
        return this->m_mouse_state & SDL_BUTTON(button);
    }
}