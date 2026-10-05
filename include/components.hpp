#pragma once

#include "scripting.hpp"
#include "ecs-lua-bridge.hpp"

namespace engine::ecs {

struct Texture {
    const char *path;
};

struct Transform {
    float x, y, w, h;
};

void register_components(engine::Scripting& scripting, EcsLuaBridge& bridge);

}
