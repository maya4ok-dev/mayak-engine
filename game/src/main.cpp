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

constexpr int SCREEN_W = 800;
constexpr int SCREEN_H = 600;

struct Controller {
    int speed;
};

struct Name {
    std::string name;
};

struct EnemySpeed {
    int x, y;
};

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


    Entity& player = world.addEntity();
    player.components.add<Controller>("Controller", Controller{300});
    player.components.add<Name>("Name", Name{.name="player"});
    player.components.add<engine::ecs::Texture>("Texture", engine::ecs::Texture{.path="assets/player.png"});
    player.components.add<engine::ecs::Transform>("Transform", engine::ecs::Transform{.x=100, .y=100, .w=50, .h=50});
    player.components.add<AABB>("AABB", AABB{.x=100, .y=100, .w=50, .h=50});

    for (int i = 0; i < 10; i++) {
        // 0 left
        // 1 right
        // 2 top
        // 3 bottom
        const int side = std::rand() % 4;

        engine::ecs::Transform transform = {.w = 25, .h = 25};
        EnemySpeed speed = {0};

        if (side == 0) {
            transform.x = -transform.w;
            transform.y = rand() % SCREEN_H;
            speed.x = 1;
            speed.y = rand() % 3 - 1;
        } else if (side == 1) {
            transform.x = SCREEN_W;
            transform.y = rand() % SCREEN_H;
            speed.x = -1;
            speed.y = rand() % 3 - 1;
        } else if (side == 2) {
            transform.y = -transform.h;
            transform.x = rand() % SCREEN_W;
            speed.y = 1;
            speed.x = rand() % 3 - 1;
        } else if (side == 3) {
            transform.y = SCREEN_H;
            transform.x = rand() % SCREEN_W;
            speed.y = -1;
            speed.x = rand() % 3 - 1;
        }
    
        Entity& enemy = world.addEntity();
        enemy.components.add<Name>("Name", Name{.name="enemy"});
        enemy.components.add<engine::ecs::Texture>("Texture", engine::ecs::Texture{.path="assets/enemy.png"});
        enemy.components.add<engine::ecs::Transform>("Transform", transform);
        enemy.components.add<AABB>("AABB", AABB{.x=transform.x, .y=transform.y, .w=transform.w, .h=transform.h});
        enemy.components.add<EnemySpeed>("EnemySpeed", speed);
    }

    mayak::gfx::setVSync(true);
    if (!mayak::gfx::init("Window", SCREEN_W, SCREEN_H)) {
        mlogger.setLevel(error) << "failed to initialize SDL!" << mayak::logger::core::flush;
    }

    mayak::gfx::setBackground(30, 30, 46);

    auto resolution = mayak::gfx::resolution();

    Entity& camera_entity = world.addEntity();
    camera_entity.components.add<Name>("Name", Name{.name="camera"});
    auto &camera = camera_entity.components.add<engine::components::Camera>("Camera", engine::components::Camera{
        .x = 0,
        .y = 0,
        .w = static_cast<float>(SCREEN_W),
        .h = static_cast<float>(SCREEN_H)
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
