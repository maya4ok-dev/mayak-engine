#include "ScriptComponent.hpp"
#include "../ECS/EntityManager.hpp"

namespace mayak::ecs {

    class LuaSystem {
        ComponentManager& cm;

    public:
        explicit LuaSystem(ComponentManager& cm) : cm(cm) {}

        void startAll() {
            auto& components = cm.get<LuaComponent>();
            for (auto& [entity, component] : components.getAll()) {
                component.start();
            }
        }

        void updateAll(float dt) {
            auto& components = cm.get<LuaComponent>();
            for (auto& [entity, component] : components.getAll()) {
                component.update(dt);
            }
        }

        void endAll() {
            auto& components = cm.get<LuaComponent>();
            for (auto& [entity, component] : components.getAll()) {
                component.end();
            }
        }
    };
    
}