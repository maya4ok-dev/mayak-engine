#include "scripting.hpp"
#include "world.hpp"
#include "aabb.hpp"
#include "logger.hpp"
#include "ecs-lua-bridge.hpp"

#include <sol/sol.hpp>
#include <SDL3/SDL.h>

// bind engine's api
void bind_api(sol::state& state) {
    state.new_usertype<Entity>("Entity", "components", &Entity::components);

    // World
    state.new_usertype<engine::World>("World",
        "width",
        sol::readonly(&engine::World::width),
        "height",
        sol::readonly(&engine::World::height),
        "addEntity",
        &engine::World::addEntity,
        "destroyEntity",
        &engine::World::destroyEntity,
        "getEntities",
        &engine::World::getEntities
    );

    auto world = state.create_named_table("world");

    world.set_function("add", engine::world::add);
    world.set_function("destroy", engine::world::destroy);
    world.set_function("get", engine::world::get);

    world["active"] = sol::property(
        static_cast<engine::World* (*)()>(engine::world::active),
        static_cast<void (*)(engine::World&)>(engine::world::active)
    );

    // 3. Register AxisAlignedBoundingBox usertype (hitbox)
    state.new_usertype<AxisAlignedBoundingBox>("AxisAlignedBoundingBox",
        "lowerLeftX",
        sol::readonly(
            &AxisAlignedBoundingBox::GetLowerLeftX
        ),
        "lowerLeftY",
        sol::readonly(
            &AxisAlignedBoundingBox::GetLowerLeftY
        ),
        "upperRightX",
        sol::readonly(
            &AxisAlignedBoundingBox::GetUpperRightX
        ),
        "upperRightY",
        sol::readonly(
            &AxisAlignedBoundingBox::GetUpperRightY
        )
    );

    state.set_function("isKeyPressed", [](const char *name) {
        return SDL_GetKeyboardState(nullptr)[SDL_GetScancodeFromName(name)] != 0;
    });
}

#define DEFAULT_MAIN_SCRIPT "scripts/init.lua"

engine::Scripting::Scripting() {
    state = sol::state();
    state.open_libraries(sol::lib::base, sol::lib::package, sol::lib::math, sol::lib::os);
    bind_api(state);

    try {
        state.script_file(DEFAULT_MAIN_SCRIPT);
    } catch(const sol::error &err) {
        mlogger.setLevel(error) << "[scripting] error while loading " << DEFAULT_MAIN_SCRIPT << ": " << err.what() << mayak::logger::core::flush;
    }

}

void engine::Scripting::operator()(double dt) {

    auto update = state["update"];
    if (update.valid()) {
        update(dt);
    }
}

