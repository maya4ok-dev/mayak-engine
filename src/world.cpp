#include <algorithm>

#include "world.hpp"
#include "object.hpp"

Object* engine::World::addObject(float x, float y, float h, float w, std::unordered_set<std::string> tags, const char* path, AxisAlignedBoundingBox hitbox) {
    return &objects.emplace_back(x, y, h, w, tags, path, hitbox);
}

std::vector<Object>* engine::World::getObjects() {
    return &objects;
}

void engine::World::destroyObject(Object &object) {
    objects.erase(std::remove_if(objects.begin(), objects.end(),
        [&object](Object &current) {
            return &current == &object;
        }
    ));
}
