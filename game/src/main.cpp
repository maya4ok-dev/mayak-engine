#include <SDL3/SDL.h>

#include "world.hpp"
#include "renderer.hpp"
#include "scripting.hpp"
#include "logger.hpp"

SDL_Event event;

int main() {
    init_logger();

    mayak::gfx::setVSync(true);

    engine::World world(800, 600);

    world.addObject(180, 180, 40, 40, {"player"}, "assets/imgs/pancake.bmp", AxisAlignedBoundingBox(glm::vec2(0, 0), glm::vec2(40, 40)));
    world.addObject(400, 200, 40, 40, {"rotatable"}, "assets/imgs/pancake.bmp", AxisAlignedBoundingBox(glm::vec2(0, 0), glm::vec2(40, 40)));
    world.addObject(0, 400, 200, 800, {"ground"}, "assets/imgs/ground.png", AxisAlignedBoundingBox(glm::vec2(0,0), glm::vec2(200, 800)));
    
    engine::world::active(world);

    engine::Scripting scripting;

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
