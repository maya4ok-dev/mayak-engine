#include "components.hpp"
#include "camera.hpp"
#include "aabb.hpp"

void engine::ecs::register_components(EcsLuaBridge& bridge) {
    bridge.register_component<Texture>("Texture", "path", &Texture::path);
    bridge.register_component<Transform>("Transform",
        "x", &Transform::x, "y", &Transform::y,
        "w", &Transform::w, "h", &Transform::h
    );
    bridge.register_component<engine::components::Camera>("Camera",
        "x", &engine::components::Camera::x,
        "y", &engine::components::Camera::y,
        "w", &engine::components::Camera::w,
        "h", &engine::components::Camera::h
    );
    bridge.register_component<AABB>("AABB",
        "x", &AABB::x,
        "y", &AABB::y,
        "w", &AABB::w,
        "h", &AABB::h,
        "intersects", &AABB::intersects
    );
}

