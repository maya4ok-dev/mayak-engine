#pragma once

#include <vector>

#include "ecs.hpp"

namespace engine {

class World {
    std::vector<Entity> entities;
public:
    Entity& addEntity();
    void destroyEntity(Entity& entity);
    std::vector<Entity>& getEntities();
};

namespace world {

    World* add(World& world);
    void destroy(World& world);
    std::vector<World>* get();

    World* active();
    void active(World& world);

}}
