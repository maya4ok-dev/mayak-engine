#include <algorithm>
#include "world.hpp"

Entity& engine::World::addEntity() {
    return entities.emplace_back();
}

std::vector<Entity>& engine::World::getEntities() {
    return entities;
}

void engine::World::destroyEntity(Entity &entity) {
    entities.erase(std::remove_if(entities.begin(), entities.end(),
        [&entity](Entity &current) {
            return &current == &entity;
        }
    ));
}
