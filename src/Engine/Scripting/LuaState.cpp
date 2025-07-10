// File: Engine/Scripting/LuaState.cpp
// Author: Maya4ok
// Created: 2025-07-10
// Description: Lua state wrapper and initialization

#include "Engine/Scripting/LuaState.hpp"
#include "logger.hpp"

#include <memory>

namespace { // incapulate the lua state
    static std::unique_ptr<sol::state> luaState = nullptr;
}

namespace mayak::scripting {

    bool isInitialized() { return luaState != nullptr; }

    bool init() {
        try {
            if (isInitialized()) {
                MAYAK_LOG_WARN("Lua is already initialized");
                return true;
            }

            luaState = std::make_unique<sol::state>();
            luaState->open_libraries(sol::lib::base, sol::lib::package, sol::lib::math, sol::lib::string, sol::lib::table, sol::lib::os);

            return true;

        } catch (const std::exception& e) {
            MAYAK_LOG_ERROR("Failed to initialize lua: " + std::string(e.what()));
            return false;
        }
    }

    sol::state& getLuaState() {
        if (!isInitialized()) { // throw exception if not initialized
            MAYAK_LOG_FATAL("Lua is not initialized");
            throw std::runtime_error("Lua is not initialized");
        }

        return *luaState; // return the lua state
    }

    void shutdown() {
        MAYAK_LOG_INFO("Shutting down lua");
        luaState.reset(); // null the lua state pointer
    }

}