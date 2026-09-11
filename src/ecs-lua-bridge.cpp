#include "ecs-lua-bridge.hpp"

namespace {
    std::unordered_map<std::string, engine::scripting::add_fn> add_fns;
    std::unordered_map<std::string, engine::scripting::get_fn> get_fns;
}

namespace engine::scripting {

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

}
