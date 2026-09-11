#include <sol/sol.hpp>

#include <functional>
#include <string_view>

namespace engine::scripting {
    
using add_fn = std::function<sol::object(std::string_view name, sol::table)>;
using get_fn = std::function<sol::object(std::string_view name)>;

template <typename Component, typename... Args>
add_fn register_add(std::string_view name) { }

template <typename Component>
add_fn register_add(std::string_view name) { }

add_fn* add(std::string_view name);
get_fn* get(std::string_view name);

} // namespace engine::scripting
