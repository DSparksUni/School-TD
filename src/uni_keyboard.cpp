#include "uni_keyboard.hpp"

namespace uni {
    std::shared_ptr<KeyboardListener> KeyboardListener::instance = nullptr;
    bool KeyboardListener::has_instance = false;

    void KeyboardListener::update() noexcept {
        this->m_keyboard_state = const_cast<uint8_t*>(
            SDL_GetKeyboardState(&this->m_state_len)
        );
    }

    KeyboardListener::KeyboardListener() {
        this->update();
    }

    std::shared_ptr<KeyboardListener> KeyboardListener::get() noexcept {
        if(!has_instance) {
            instance = std::shared_ptr<KeyboardListener>(new KeyboardListener());
            has_instance = true;
        }

        return instance;
    }

    nodiscard bool KeyboardListener::key_down(int key) const noexcept {
        return (key < this->m_state_len)? this->m_keyboard_state[key] : false;
    }
}