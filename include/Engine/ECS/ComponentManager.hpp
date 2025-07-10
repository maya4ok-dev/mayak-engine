#pragma once

#include <unordered_map>
#include <typeindex>
#include <memory>
#include "ComponentStorage.hpp"

namespace mayak::ecs {

class ComponentManager {
    std::unordered_map<std::type_index, std::unique_ptr<void>> storages;

public:
    template<typename T>
    ComponentStorage<T>& get() {
        std::type_index index(typeid(T));
        if (!storages.contains(index)) {
            storages[index] = std::make_unique<ComponentStorage<T>>();
        }
        return *static_cast<ComponentStorage<T>*>(storages[index].get());
    }

    void clear() {
        storages.clear();
    }
};

} // namespace mayak::ecs
