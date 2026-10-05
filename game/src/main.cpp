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
    player.components.add<engine::ecs::Texture>("Texture", engine::ecs::Texture{.path="assets/imgs/pancake.bmp"});
    player.components.add<engine::ecs::Transform>("Transform", engine::ecs::Transform{.x=100, .y=100, .w=100, .h=100});

    Entity& pancake = world.addEntity();
    pancake.components.add<Name>("Name", Name{.name="pancake"});
    pancake.components.add<engine::ecs::Texture>("Texture", engine::ecs::Texture{.path="assets/imgs/pancake.bmp"});
    pancake.components.add<engine::ecs::Transform>("Transform", engine::ecs::Transform{.x=300, .y=300, .w=50, .h=50});

    // FIXME: entity components after adding another entity are nullptrs
    auto name = player.components.get<Name>("Name");
    auto controller = player.components.get<Controller>("Controller");
    auto texture = player.components.get<engine::ecs::Texture>("Texture");

    if (name && controller && texture)
        mlogger.setLevel(info) << "initialized player named " << name->name << " with speed: " << controller->speed << " and texture: " << texture->path << mayak::logger::core::flush;
    else
        mlogger.setLevel(error) << "[player] name: " << name << "; controller: " << controller << "; texture: " << texture << mayak::logger::core::flush;

    mayak::gfx::setVSync(true);
    if (!mayak::gfx::init("Window", 800, 600)) {
        mlogger.setLevel(error) << "failed to initialize SDL!" << mayak::logger::core::flush;
    }

    auto resolution = mayak::gfx::resolution();

    engine::camera::active = {
        .x = 0,
        .y = 0,
        .w = resolution.w,
        .h = resolution.h
    };

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

        mayak::gfx::render(engine::camera::active);
    }
    mayak::gfx::cleanup();
    SDL_Quit();
    return 0;
}
