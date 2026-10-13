#pragma once

#include <unordered_map>

#include "ecs.hpp"
#include "world.hpp"
#include "components.hpp"

struct EntityPosition {
    float x, y, w, h;
};

namespace engine::components {

struct Camera {
    float x, y, w, h;

    std::unordered_map<Entity*, EntityPosition> relative(engine::World& world) {
        std::unordered_map<Entity*, EntityPosition> result;

        for (auto &entity : world.getEntities()) {
            auto transform = entity.components.get<engine::ecs::Transform>("Transform");
            if (!transform) continue;

            EntityPosition entity_position = {
                .x = transform->x - x,
                .y = transform->y - y,
                .w = transform->w,
                .h = transform->h
            };
            result[&entity] = entity_position;
        }

        return result;
    }
};

}

