#include <SDL3/SDL.h>

#include "dimension.hpp"
#include "renderer.hpp"
#include "scripting.hpp"
#include "logger.hpp"

std::vector<DIM> DIM::dims;
SDL_Event event;

int main() {
    init_logger();

    mayak::gfx::setVSync(true);


    DIM world(800, 600);

    world.AddObject(180, 180, 40, 40, {"player"}, "assets/imgs/pancake.bmp", AxisAlignedBoundingBox(glm::vec2(0, 0), glm::vec2(40, 40)));
    world.AddObject(400, 200, 40, 40, {"rotatable"}, "assets/imgs/pancake.bmp", AxisAlignedBoundingBox(glm::vec2(0, 0), glm::vec2(40, 40)));
    world.AddObject(0, 400, 200, 800, {"ground"}, "assets/imgs/ground.png", AxisAlignedBoundingBox(glm::vec2(0,0), glm::vec2(200, 800)));
    
    DIM::SetCurrDIM(&world);

    Script::Init();

    if (!mayak::gfx::init("Window")) {
        mlogger.setLevel(error);
        mlogger << "failed to initialize SDL!" << mayak::logger::core::flush;
    }

    bool running = true;
    while (running) {
        Script::Run();
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) running = false;
        }

        mayak::gfx::render();
    }
    mayak::gfx::cleanup();
    SDL_Quit();
    return 0;
}
