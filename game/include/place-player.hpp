#pragma once

#include <camera.hpp>
#include <ecs.hpp>
#include <logger.hpp>

inline void place_player(Entity& camera_entity, Entity& player_entity) {
    // mlogger.setLevel(debug)
        // << "camera: " << &camera_entity << "; "
        // << "player: " << &player_entity << mayak::logger::core::flush;
    engine::components::Camera* camera = camera_entity.components.get<engine::components::Camera>("Camera");
    engine::ecs::Transform* transform = player_entity.components.get<engine::ecs::Transform>("Transform");
    if (!camera || !transform) {
        mlogger.setLevel(error)
            << "camera component: " << camera << "; "
            << "transform component: " << transform
            << mayak::logger::core::flush;
        return;
    }

    transform->x = camera->x + (camera->w - transform->w) / 2;
    transform->y = camera->y + (camera->h - transform->h) / 2;
}
