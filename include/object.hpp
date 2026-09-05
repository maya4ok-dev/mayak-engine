#pragma once

#include "aabb.hpp"

#include <unordered_set>
#include <string>

struct Object {
    float posX, posY, height, width;
    const char* path;
    std::unordered_set<std::string> tags;
    bool isVisible;
    AxisAlignedBoundingBox hitbox;

    Object(float posX, float posY, float height, float width, std::unordered_set<std::string> tags, const char* path, AxisAlignedBoundingBox hitbox)
    : posX(posX), posY(posY), height(height), width(width), path(path), tags(tags), hitbox(hitbox) {}

    ~Object() {}

    // Getters
    float GetPosX() const { return posX; }
    float GetPosY() const { return posY; }
    float GetHeight() const { return height; }
    float GetWidth() const { return width; }
    const std::string GetPath() const { return path; }
    bool HasTag(const std::string& tag) const { return tags.find(tag) != tags.end(); }
    bool IsVisible() const { return isVisible; }

    // Setters
    void SetPosX(const float &x) { posX = x; }
    void SetPosY(float y) { posY = y; }
    void SetHeight(float h) { height = h; }
    void SetWidth(float w) { width = w; }
    void SetPath(const char * p) { path = p; }
    void AddTag(const std::string& tag) { tags.insert(tag); }
    void RemoveTag(const std::string& tag) { tags.erase(tag); }
    void SetVisible(bool state) { isVisible = state; }
};

