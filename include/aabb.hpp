#pragma once

#include <glm/vec2.hpp>

struct AxisAlignedBoundingBox {
    glm::vec2 lowerLeft;
    glm::vec2 upperRight;

    AxisAlignedBoundingBox(const glm::vec2& ll, const glm::vec2& ur)
        : lowerLeft(ll), upperRight(ur) {}

    AxisAlignedBoundingBox(const glm::vec2& position, float width, float height)
        : lowerLeft(position), upperRight(glm::vec2(position.x + width, position.y + height)) {}

    bool Intersects(const AxisAlignedBoundingBox& other) const {
        return !(upperRight.x < other.lowerLeft.x ||
                 lowerLeft.x > other.upperRight.x ||
                 upperRight.y < other.lowerLeft.y ||
                 lowerLeft.y > other.upperRight.y);
    }

    // Getters
    float GetLowerLeftX() const { return lowerLeft.x; }
    float GetLowerLeftY() const { return lowerLeft.y; }
    float GetUpperRightX() const { return upperRight.x; }
    float GetUpperRightY() const { return upperRight.y; }
};
