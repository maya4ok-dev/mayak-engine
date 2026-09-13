#include <SDL3/SDL.h>
#include <sol/sol.hpp>

#include "mayak/logger/core/logger.hpp"
#include "world.hpp"
#include "renderer.hpp"
#include "scripting.hpp"
#include "logger.hpp"
#include "ecs.hpp"
#include "ecs-lua-bridge.hpp"

struct Controller {
    int speed;
};

struct Name {
    std::string name;
};

int main() {
    init_logger();

    engine::World world(800, 600);
    engine::world::active(world);

    engine::Scripting scripting;

    engine::scripting::register_component<Controller>(
        "Controller", scripting,
        "speed", &Controller::speed
    );

    engine::scripting::register_component<Name>(
        "Name", scripting, 
        "name", &Name::name
    );

    mayak::gfx::register_components(scripting);

    Entity& player = world.addEntity();
    player.components.add<Controller>("Controller", Controller{300});
    player.components.add<Name>("Name", Name{.name="player"});
    player.components.add<mayak::gfx::Texture>("Texture", mayak::gfx::Texture{.path="assets/imgs/pancake.bmp"});
    player.components.add<mayak::gfx::Transform>("Transform", mayak::gfx::Transform{.x=100, .y=100, .w=100, .h=100});

    auto name = player.components.get<Name>("Name");
    auto controller = player.components.get<Controller>("Controller");
    auto texture = player.components.get<mayak::gfx::Texture>("Texture");

    if (name && controller && texture)
        mlogger.setLevel(info) << "initialized player named " << name->name << " with speed: " << controller->speed << " and texture: " << texture->path << mayak::logger::core::flush;
    else
        mlogger.setLevel(error) << "name or controller is null!";

    mayak::gfx::setVSync(true);
    if (!mayak::gfx::init("Window")) {
        mlogger.setLevel(error) << "failed to initialize SDL!" << mayak::logger::core::flush;
    }

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

        mayak::gfx::render();
    }
    mayak::gfx::cleanup();
    SDL_Quit();
    return 0;
}
