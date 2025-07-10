// File: Engine/Scripting/LuaState.hpp
// Author: Maya4ok
// Created: 2025-07-10
// Description: Lua state wrapper and initialization

#pragma once

#include <sol/sol.hpp>

namespace mayak::scripting {

    /// @brief  Checks if the lua state is initialized
    /// @return True if the lua state is initialized, false otherwise
    bool isInitialized();

    /// @brief Returns the lua state
    /// @return The lua state
    sol::state& getLuaState();

    /// @brief Initializes the lua state
    /// @return True if the lua state is initialized successfully, false otherwise
    bool init();

    /// @brief Shuts down the lua state
    /// @details Nulls the lua state pointer
    void shutdown();
}