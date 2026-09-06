#include <any>
#include <typeindex>
#include <unordered_map>

class ComponentStorage {
    std::unordered_map<std::type_index, std::any> components;

public:
    template<typename Component, typename... Args>
    void add(Args&&... args);

    template<typename Component>
    Component* get();
};

struct Entity {
    ComponentStorage components;
};
