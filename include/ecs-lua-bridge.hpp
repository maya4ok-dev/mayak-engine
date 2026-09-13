#include "ecs.hpp"
#include "scripting.hpp"
#include <sol/object.hpp>
#include <sol/raii.hpp>
#include <sol/sol.hpp>

#include <type_traits>
#include <unordered_map>
#include <functional>
#include <string_view>
#include <tuple>
#include <utility>

namespace engine::scripting {

using add_fn = std::function<sol::object(Entity &entity, std::string_view name, sol::table)>;
using get_fn = std::function<void(sol::table& table, Entity &entity, std::string_view name)>;

namespace {
    std::unordered_map<std::string, add_fn> add_fns;
    std::unordered_map<std::string, get_fn> get_fns;
}

template <typename Component, typename Name, typename Member, typename... Args>
void set_members(
    Component& component,
    sol::table table,
    Name&& name,
    Member&& member,
    Args&&... args
) {
    using MemberType = std::remove_cvref_t<decltype(component.*member)>;
    component.*member = table[name].template get<MemberType>();

    if constexpr (sizeof...(Args) > 0)
        set_members(
            component,
            table,
            std::forward<Args>(args)...
        );
}

template <typename Component, typename Name, typename Member, typename... Args>
void get_members(
    const Component& component,
    sol::table& table,
    Name&& name,
    Member&& member,
    Args&&... args
) {
    table[name] = component.*member;

    if constexpr (sizeof...(Args) > 0)
        get_members(
            component,
            table,
            std::forward<Args>(args)...
        );
}

template <typename Component, typename... Args>
void register_add(std::string_view type, Args&&... args) {
    auto fields = std::make_tuple(std::forward<Args>(args)...);

    add_fns.emplace(type, 
        [fields = std::move(fields)] (Entity &entity, std::string_view component_name, sol::table table) {
            auto &component = entity.components.add<Component>(component_name);

            std::apply(
                [&](auto&&... args) {
                    set_members(component, table, std::forward<decltype(args)>(args)...);
                },
                fields
            );

            return sol::make_object(
                table.lua_state(),
                component
            );
        }
    );
}

template <typename Component, typename... Args>
void register_get(std::string_view type, Args&&... args) {
    auto fields = std::make_tuple(std::forward<Args>(args)...);

    get_fns.emplace(type,
        [fields = std::move(fields)](sol::table& table, Entity &entity, std::string_view component_name) {
            const auto* component = entity.components.get<Component>(component_name);
            if (!component)
                return;

            std::apply(
                [&](auto&&... args) {
                    get_members(*component, table, std::forward<decltype(args)>(args)...);
                },
                fields
            );
        }
    );
}

template <typename Component, typename... Args>
void register_component(std::string_view name, Scripting& scripting, Args&&... args) {
    scripting.bind<Component>(name, sol::constructors<Component()>());
    register_add<Component>(name, std::forward<Args>(args)...);
    register_get<Component>(name, std::forward<Args>(args)...);

    auto add_it = add_fns.find(std::string(name));
    if (add_it != add_fns.end())
        scripting.bind("entity_add_component", add_it->second);

    auto get_it = get_fns.find(std::string(name));
    if (get_it != get_fns.end())
        scripting.bind("entity_get_component", 
            [&scripting](Entity &entity, std::string_view name) {
                auto table = scripting.add_table();
                auto it = get_fns.find(std::string(name));
                if (it != get_fns.end())
                    it->second(table, entity, name);
                return table;
            }
        );
}

} // namespace engine::scripting
