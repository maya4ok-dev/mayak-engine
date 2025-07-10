#pragma once

#include <unordered_map>
#include <SDL3/SDL.h>
#include <string>

namespace mayak::input {
    extern const std::unordered_map<std::string, SDL_Scancode> keyMap;
}
