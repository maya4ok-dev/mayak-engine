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

#include "enemy.hpp"
#include "config.hpp"
#include "game-components.hpp"
#include "place-player.hpp"

int main() {
    init_logger();

    std::srand(std::time(nullptr));

    engine::World world;
    engine::world::active(world);

    engine::Scripting scripting;
    EcsLuaBridge bridge(scripting.get());

    bridge.register_component<Controller>(
        "Controller", "speed", &Controller::speed
    );

    bridge.register_component<Name>(
        "Name", "name", &Name::name
    );

    bridge.register_component<EnemySpeed>("EnemySpeed",
        "x", &EnemySpeed::x,
        "y", &EnemySpeed::y
    );

    engine::ecs::register_components(bridge);

    Entity& camera_entity = world.addEntity();
    camera_entity.components.add<Name>("Name", Name{.name="camera"});
    auto &camera = camera_entity.components.add<engine::components::Camera>("Camera", engine::components::Camera{
        .x = 0,
        .y = 0,
        .w = static_cast<float>(SCREEN_W),
        .h = static_cast<float>(SCREEN_H)
    });

    Entity& player = world.addEntity();
    player.components.add<Controller>("Controller", Controller{300});
    player.components.add<Name>("Name", Name{.name="player"});
    player.components.add<engine::ecs::Texture>("Texture", engine::ecs::Texture{.path="assets/player.png"});
    player.components.add<engine::ecs::Transform>("Transform", engine::ecs::Transform{.x=100, .y=100, .w=50, .h=50});
    player.components.add<AABB>("AABB", AABB{.x=100, .y=100, .w=50, .h=50});

    for (int i = 0; i < 10; i++) {
        auto &entity = world.addEntity();
        entity.components.add<Name>("Name", Name{.name="enemy"});
        entity.components.add<engine::ecs::Texture>("Texture", engine::ecs::Texture{.path="assets/enemy.png"});
        place_enemy(entity);
    }

    scripting.bind("place_enemy", &place_enemy);
    scripting.bind("place_player", &place_player);

    mayak::gfx::setVSync(true);
    if (!mayak::gfx::init("Window", SCREEN_W, SCREEN_H)) {
        mlogger.setLevel(error) << "failed to initialize SDL!" << mayak::logger::core::flush;
    }

    mayak::gfx::setBackground(30, 30, 46);

    auto resolution = mayak::gfx::resolution();

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
