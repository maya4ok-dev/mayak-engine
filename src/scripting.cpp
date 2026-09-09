// File: ScriptEngine.cpp

#include "scripting.hpp"
#include "keymap.hpp"
#include "mayak/logger/core/logger.hpp"
#include "world.hpp"
#include "aabb.hpp"
#include "object.hpp"
#include "logger.hpp"

#include <sol/sol.hpp>
#include <SDL3/SDL.h>

// bind engine's api
void bind_api(sol::state& state) {
    // 1. Register Object usertype
    state.new_usertype<Object>("Object",
        "posX",
        sol::property(
            &Object::GetPosX, &Object::SetPosX
        ),
        "posY",
        sol::property(
            &Object::GetPosY, &Object::SetPosY
        ),
        "height",
        sol::property(
            &Object::GetHeight, &Object::SetHeight
        ),
        "width",
        sol::property(
            &Object::GetWidth, &Object::SetWidth
        ),
        "path",
        sol::property(
            &Object::GetPath, &Object::SetPath
        ),
        "tags",
        sol::property([](Object& obj) {
            return sol::as_table(obj.tags);
        })
    );

    // World
    state.new_usertype<engine::World>("World",
        "width",
        sol::readonly(
            &engine::World::width
        ),
        "height",
        sol::readonly(
            &engine::World::height
        ),
        "addObject",
        &engine::World::addObject,
        "destroyObject",
        &engine::World::destroyObject,
        "getObjects",
        &engine::World::getObjects
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

    // 4. Registrating key scancodes
    for (const auto& [name, code] : keyMap) {
        state["KEY_" + name] = code;
    }
    
    // 5. Registrating check the keypress function
    state.set_function("isKeyPressed", [](SDL_Scancode scancode) {
        const bool* keyboardState = SDL_GetKeyboardState(nullptr);
        return keyboardState[scancode] != 0;
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

