#include "components.hpp"

void engine::ecs::register_components(engine::Scripting& scripting, EcsLuaBridge& bridge) {
    scripting.bind<Texture>("Texture", "path", &Texture::path);
    scripting.bind<Transform>("Transform",
        "x", &Transform::x, "y", &Transform::y,
        "w", &Transform::w, "h", &Transform::h
    );
    bridge.register_component<Texture>("Texture", "path", &Texture::path);
    bridge.register_component<Transform>("Transform",
        "x", &Transform::x, "y", &Transform::y,
        "w", &Transform::w, "h", &Transform::h
    );
}

