#include <sol/sol.hpp>
#include <functional>
#include <string>
#include <string_view>
#include <unordered_map>

namespace engine::scripting {

inline struct ComponentBridge {
    using add_fn = std::function<sol::object(std::string_view name, sol::table)>;
    using get_fn = std::function<sol::object(std::string_view name)>;

    // TODO: TBD
    template <typename Component, typename... Args>
    add_fn register_add(std::string_view name) { }

    // TODO: TBD
    template <typename Component>
    get_fn register_get(std::string_view name) { }

    add_fn* add(std::string_view name) {
        auto it = add_fns.find(std::string(name));
        if (it == add_fns.end())
            return nullptr;
        return &it->second;
    }
    get_fn* get(std::string_view name) {
        auto it = get_fns.find(std::string(name));
        if (it == get_fns.end())
            return nullptr;
        return &it->second;
    }
private:
    std::unordered_map<std::string, add_fn> add_fns;
    std::unordered_map<std::string, get_fn> get_fns;
} component_bridge;

}
