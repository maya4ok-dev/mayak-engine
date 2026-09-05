#pragma once

#include <vector>
#include <unordered_set>

#include "aabb.hpp"
#include "object.hpp"

namespace engine {

class World {
    std::vector<Object> objects;
public:
    int width, height;

    World(int width, int height) : width(width), height(height) {}

    Object* addObject(float x, float y, float h, float w, std::unordered_set<std::string> tags, const char* path, AxisAlignedBoundingBox hitbox);

    void destroyObject(Object &object);
    std::vector<Object>* getObjects();
};

namespace world {

    World* add(World& world);
    void destroy(World& world);
    std::vector<World>* get();

    World* active();
    void active(World& world);

}}
