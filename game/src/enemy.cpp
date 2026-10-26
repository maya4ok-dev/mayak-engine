#include <cstdlib>

#include <components.hpp>
#include <ecs.hpp>
#include <aabb.hpp>
#include <world.hpp>
#include <logger.hpp>

#include "enemy.hpp"
#include "config.hpp"
#include "game-components.hpp"

void place_enemy(Entity& entity) {
    auto transform = entity.components.get<engine::ecs::Transform>("Transform");
    auto speed = entity.components.get<EnemySpeed>("EnemySpeed");
    auto hitbox = entity.components.get<AABB>("AABB");

    if (!transform)
        transform = &entity.components.add<engine::ecs::Transform>("Transform",
            engine::ecs::Transform{.x = 0, .y = 0, .w = 25, .h = 25});
    if (!speed)
        speed = &entity.components.add<EnemySpeed>("EnemySpeed", EnemySpeed{0});

    // 0 left
    // 1 right
    // 2 top
    // 3 bottom
    const int side = std::rand() % 4;

    if (side == 0) {
        transform->x = -transform->w;
        transform->y = std::rand() % SCREEN_H;
        speed->x = 1;
        speed->y = std::rand() % 3 - 1;
    } else if (side == 1) {
        transform->x = SCREEN_W;
        transform->y = std::rand() % SCREEN_H;
        speed->x = -1;
        speed->y = std::rand() % 3 - 1;
    } else if (side == 2) {
        transform->y = -transform->h;
        transform->x = std::rand() % SCREEN_W;
        speed->y = 1;
        speed->x = std::rand() % 3 - 1;
    } else if (side == 3) {
        transform->y = SCREEN_H;
        transform->x = std::rand() % SCREEN_W;
        speed->y = -1;
        speed->x = std::rand() % 3 - 1;
    }

    if (!hitbox)
        hitbox = &entity.components.add<AABB>("AABB",
            AABB{.x = transform->x, .y = transform->y,
                 .w = transform->w, .h = transform->h});
}
