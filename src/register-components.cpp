#include "components.hpp"

void engine::ecs::register_components(EcsLuaBridge& bridge) {
    bridge.register_component<Texture>("Texture", "path", &Texture::path);
    bridge.register_component<Transform>("Transform",
        "x", &Transform::x, "y", &Transform::y,
        "w", &Transform::w, "h", &Transform::h
    );
}

