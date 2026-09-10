#pragma once

#include <any>
#include <string>
#include <string_view>
#include <unordered_map>

class ComponentStorage {
    std::unordered_map<std::string, std::any> components;

public:
    template<typename Component, typename... Args>
    void add(std::string_view name, Args&&... args) {
        auto component = std::make_any<Component>(std::forward<Args>(args)...);
        components.emplace(
            name,
            std::move(component)
        );
    }

    template<typename Component>
    Component* get(std::string_view name) {
        auto it = components.find(name.data());
        if (it == components.end())
            return nullptr;

        return std::any_cast<Component>(&it->second);
    }
};

struct Entity {
    ComponentStorage components;
};
