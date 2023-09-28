#include "uni_tower.hpp"

namespace uni {
    Tower::Tower(SDL_Rect rect): m_rect(rect) {}
    Tower::Tower(int x, int y, int w, int h): m_rect{x, y, w, h} {}

    nodiscard SDL_Rect Tower::rect() const noexcept {
        return this->m_rect;
    }


    TestTower::TestTower(circle c): super{UNI_UNPACK_CIRCLE(c), c.r} {}
    TestTower::TestTower(int x, int y, int r): super{x, y, r, r} {}

    void TestTower::draw(std::unique_ptr<Window>& window) const noexcept {
      circle mapped_circle = window->map_circle(
        this->m_rect.x, this->m_rect.y, this->m_rect.w
      );

      filledCircleColor(
        window->render(), UNI_UNPACK_CIRCLE(mapped_circle), 0xFF00FFFF
      );
    }

    void TestTower::update(double dt) noexcept {

    }

    nodiscard circle TestTower::get_circle() const noexcept {
      return circle{
        static_cast<short>(this->m_rect.x),
        static_cast<short>(this->m_rect.y),
        static_cast<short>(this->m_rect.w)
      };
    }
}
