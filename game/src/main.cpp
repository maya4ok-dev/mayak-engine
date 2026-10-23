#include <SDL3/SDL.h>
#include <sol/sol.hpp>

#include "camera.hpp"
#include "world.hpp"
#include "renderer.hpp"
#include "scripting.hpp"
#include "logger.hpp"
#include "ecs.hpp"
#include "ecs-lua-bridge.hpp"
#include "components.hpp"
#include "aabb.hpp"

struct Controller {
    int speed;
};

struct Name {
    std::string name;
};

int main() {
    init_logger();

    engine::World world;
    engine::world::active(world);

    engine::Scripting scripting;
    EcsLuaBridge bridge(scripting.get());

    bridge.register_component<Controller>(
        "Controller",
        "speed", &Controller::speed
    );

    bridge.register_component<Name>(
        "Name",
        "name", &Name::name
    );

    engine::ecs::register_components(bridge);

    Entity& player = world.addEntity();
    player.components.add<Controller>("Controller", Controller{300});
    player.components.add<Name>("Name", Name{.name="player"});
    player.components.add<engine::ecs::Transform>("Transform", engine::ecs::Transform{.x=100, .y=100, .w=50, .h=50});
    player.components.add<AABB>("AABB", AABB{.x=100, .y=100, .w=50, .h=50});

    Entity& enemy = world.addEntity();
    enemy.components.add<Name>("Name", Name{.name="enemy"});
    enemy.components.add<engine::ecs::Texture>("Texture", engine::ecs::Texture{.path="assets/enemy.png"});
    enemy.components.add<engine::ecs::Transform>("Transform", engine::ecs::Transform{.x=300, .y=300, .w=50, .h=50});
    enemy.components.add<AABB>("AABB", AABB{.x=300, .y=300, .w=100, .h=100});

    mayak::gfx::setVSync(true);
    if (!mayak::gfx::init("Window", 800, 600)) {
        mlogger.setLevel(error) << "failed to initialize SDL!" << mayak::logger::core::flush;
    }

    auto resolution = mayak::gfx::resolution();

    Entity& camera_entity = world.addEntity();
    camera_entity.components.add<Name>("Name", Name{.name="camera"});
    auto &camera = camera_entity.components.add<engine::components::Camera>("Camera", engine::components::Camera{
        .x = 0,
        .y = 0,
        .w = static_cast<float>(resolution.w),
        .h = static_cast<float>(resolution.h)
    });

    const auto freq = SDL_GetPerformanceFrequency();
    auto last = SDL_GetPerformanceCounter();

    SDL_Event event;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) running = false;
        }

        const auto now = SDL_GetPerformanceCounter();
        const double dt = static_cast<double>(now - last) / freq;

        last = now;

        SDL_PumpEvents();
        scripting(dt);

        mayak::gfx::render(camera);
    }
    mayak::gfx::cleanup();
    SDL_Quit();
    return 0;
}
