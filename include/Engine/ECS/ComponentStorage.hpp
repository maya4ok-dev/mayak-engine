#pragma once

#include <unordered_map>
#include <cstdint>

namespace mayak::ecs {

using Entity = uint32_t;

template<typename T>
class ComponentStorage {
    std::unordered_map<Entity, T> components;

public:
    void add(Entity entity, const T& component) {
        components[entity] = component;
    }

    void remove(Entity entity) {
        components.erase(entity);
    }

    bool has(Entity entity) const {
        return components.contains(entity);
    }

    T* get(Entity entity) {
        auto it = components.find(entity);
        return it != components.end() ? &it->second : nullptr;
    }

    std::unordered_map<Entity, T>& getAll() const {
        return components;
    }
};

} // namespace mayak::ecs
