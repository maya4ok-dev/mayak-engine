#pragma once

#include <unordered_map>

#include "ecs.hpp"
#include "world.hpp"
#include "components.hpp"

struct EntityPosition {
    int x, y, w, h;
};

class Camera {
public:
    int x, y, w, h;

    std::unordered_map<Entity*, EntityPosition> relative(engine::World& world) {
        std::unordered_map<Entity*, EntityPosition> result;

        for (auto &entity : world.getEntities()) {
            auto transform = entity.components.get<engine::ecs::Transform>("Transform");
            if (!transform) continue;

            EntityPosition entity_position;
            entity_position.x = transform->x - x;
            entity_position.y = transform->y - y;
            entity_position.w = transform->w;
            entity_position.h = transform->h;
            
            result[&entity] = entity_position;
        }

        return result;
    }
};

namespace engine::camera {

    inline Camera active;

}
