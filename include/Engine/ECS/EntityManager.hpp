#pragma once
#include "ComponentManager.hpp"
#include "Components/Transform.hpp"
#include "Components/Tags.hpp"
#include <iostream>

namespace mayak::ecs {

class RenderSystem : public ISystem {
    ComponentManager& cm;

public:
    RenderSystem(ComponentManager& cm) : cm(cm) {}

    void update(float dt) override {
        auto& transforms = cm.get<Transform>();
        auto& tags = cm.get<Tags>();

        for (auto& [entity, transform] : transforms.getAll()) {
            if (tags.has(entity)) {
                std::cout << "Render " << tags.get(entity)->tags.size()
                          << " tags at (" << transform.x << ", " << transform.y << ")\n";
            }
        }
    }
};

}
