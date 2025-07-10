// File: Engine/Scripting/ScriptComponent.hpp
// Author: Maya4ok
// Created: 2025-07-10
// Description: Script component for entities

#pragma once
#include <string>
#include <sol/sol.hpp>

namespace mayak::ecs {

    struct LuaComponent {
        std::string scriptName;
        sol::state* luaState;
        sol::table scriptTable;

        LuaComponent() = default;
        
        LuaComponent(sol::state& lua, const std::string& script) : scriptName(script), luaState(&lua) {
            luaState->script_file(scriptName);
            scriptTable = (*luaState)[scriptName];
        }

        void start() {
            if (scriptTable.valid()) {
                sol::function f = scriptTable["start"];
                if (f.valid()) f();
            }
        }

        void update(float dt) {
            if (scriptTable.valid()) {
                sol::function f = scriptTable["update"];
                if (f.valid()) f(dt);
            }
        }

        void end() {
            if (scriptTable.valid()) {
                sol::function f = scriptTable["end"];
                if (f.valid()) f();
            }
        }
    };
    
}