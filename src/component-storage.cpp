#include "ecs.hpp"
#include <utility>
#include <any>

template<typename Component, typename... Args>
void ComponentStorage::add(Args&&... args) {
    auto component = std::make_any<Component>(std::forward<Args>(args)...);
    components.emplace(
        std::type_index(typeid(Component)),
        std::move(component)
    );
}


template<typename Component>
Component* ComponentStorage::get() {
    for (auto& component : components) {
        if (component.first == std::type_index(typeid(Component))) {
            return std::any_cast<Component>(&component.second);
        }
    }

    return nullptr;
}
