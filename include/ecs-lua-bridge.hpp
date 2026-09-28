#pragma once

#include "ecs.hpp"
#include "logger.hpp"

#include <sol/sol.hpp>

#include <unordered_map>
#include <functional>
#include <utility>

class EcsLuaBridge {
    std::unordered_map<std::string, std::function<sol::object(sol::this_state, Entity&)>> getters;
    sol::state_view lua;

public:
    EcsLuaBridge(sol::state_view state) : lua(state) {
        auto entity_ut = state.new_usertype<Entity>("Entity", "components", &Entity::components);

        entity_ut.set_function("get", [this](Entity& entity, sol::this_state state, const std::string& name) -> sol::object {
            sol::state_view lua(state);

            auto it = getters.find(name);
            if (it == getters.end()) 
                return sol::make_object(lua, sol::lua_nil);

            return it->second(state, entity);
        });
    }

    template <typename T, typename... Bindings>
    void register_component(std::string name, Bindings&&... bindings) {
        mlogger.setLevel(debug) << "registring component " << name << mayak::logger::core::flush;

        auto usertype = lua.new_usertype<T>(name, sol::constructors<T()>(), std::forward<Bindings>(bindings)...);
        getters.emplace(name, [name](sol::this_state state, Entity& entity) -> sol::object {
            sol::state_view lua(state);

            T* component = entity.components.get<T>(name);
            if (!component)
                return sol::make_object(lua, sol::lua_nil);

            return sol::make_object(lua, component);

        });
    }
};
