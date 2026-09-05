#include <algorithm>
#include <vector>

#include "world.hpp"


namespace engine::world {

namespace {
    std::vector<World> worlds;
    World* active_world;
}

World* add(World& world) {
    return &worlds.emplace_back(std::move(world));
}

void destroy(World& world) {
    worlds.erase(std::remove_if(worlds.begin(), worlds.end(),
        [&world](World& current) {
            return &current == &world;
        }),
        worlds.end()
    );
}

std::vector<World>* get() {
    return &worlds;
}

World* active() {
    return active_world;
}

void active(World& world) {
    active_world = &world;
}

}
