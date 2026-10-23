#pragma once

struct AABB {
    float x, y, w, h;

    [[nodiscard]]
    bool intersects(const AABB &other) const {
        return x < other.x + other.w &&
               x + w > other.x &&
               y < other.y + other.h &&
               y + h > other.y;
    }
};
