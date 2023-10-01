#pragma once

#include <iostream>
#include <memory>

#include "SDL/SDL.h"

#include "uni_util.hpp"

namespace uni {
    class KeyboardListener {
    public:
        void update() noexcept;
    private:
        using self = KeyboardListener;

        static std::shared_ptr<self> instance;
        static bool has_instance;

        uint8_t* m_keyboard_state;
        int m_state_len;

        KeyboardListener();

    public:
        static std::shared_ptr<self> get() noexcept;

        nodiscard bool key_down(int key) const noexcept;
    };
}