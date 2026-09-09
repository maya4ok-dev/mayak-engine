#include <any>
#include <typeindex>
#include <unordered_map>

class ComponentStorage {
    std::unordered_map<std::type_index, std::any> components;

public:
    template<typename Component, typename... Args>
    void add(Args&&... args) {
        auto component = std::make_any<Component>(std::forward<Args>(args)...);
        components.emplace(
            std::type_index(typeid(Component)),
            std::move(component)
        );
    }


    template<typename Component>
    Component* get() {
        for (auto& component : components) {
            if (component.first == std::type_index(typeid(Component))) {
                return std::any_cast<Component>(&component.second);
            }
        }

        return nullptr;
    }
};

struct Entity {
    ComponentStorage components;
};
