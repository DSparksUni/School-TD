#include "uni_util.hpp"

namespace uni {
    double distance(double x1, double y1, double x2, double y2) noexcept {
        return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    }
    double distance(vec2d p1, vec2d p2) noexcept {
        return distance(p1.x, p1.y, p2.x, p2.y);
    }
    double distance(vec2d p1, double x2, double y2) noexcept {
        return distance(p1.x, p1.y, x2, y2);
    }
    double distance(double x1, double y1, vec2d p2) noexcept {
        return distance(p2, x1, y1);
    }
}