// File: ScriptEngine.cpp

#include "KeyMap.hpp"
#include "Scripting.hpp"
#include "DIM.hpp"
#include <filesystem>
#include <SDL3/SDL.h>
#include <lua.h>

bool VSync;
std::vector<std::shared_ptr<sol::state>> states;

// Loads all Lua scripts from 'scripts/' and initializes their sol2 states
void Script::Init() {
    if (!states.empty()) {
//        MAYAK_LOG_WARN("Scripts already loaded, skipping...");
        return;
    }
    // 1. Find all Lua scripts from 'scripts/'
    for (const auto& entry : std::filesystem::directory_iterator("scripts")) {

        // 2. Get script path from entry and check for script
        std::string script = entry.path().string();

        std::string ext = entry.path().extension().string();
        std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

        if (!entry.is_regular_file() || ext != ".lua") {
//            MAYAK_LOG_WARN("Skipping non-script file: " + script);
            continue;
        }

//        MAYAK_LOG_INFO("Loading script: " + script);

        // 3. Creating SOL2 states
        std::shared_ptr<sol::state> state = std::make_shared<sol::state> ();

        // 4. Opening LUA libraries
        state->open_libraries(sol::lib::base, sol::lib::package, sol::lib::math, sol::lib::os);

        // 5. Register bindings method
        Script::RegisterBindings(*state);

        // 6. Load .lua file and catch errors
        try {
            state->script_file(script);
            states.emplace_back(std::move(state));
        } catch (const sol::error& error) {
        }
    }

}

// // Object vector to table convertor
// sol::table ObjectsToTable(sol::state& state, const std::vector<Object>&objects) {
//     Logging::info("Convert Object vector to LUA table...");
//     sol::table objectTable = state.create_table();
//     for(size_t i = 0; i < objects.size(); i++) {
//         Logging::trace("Adding object objects[" + std::to_string(i) + "] to SOL2 table");
//         objectTable[i + 1] = objects[i];
//     }
//     return objectTable;
// }

// Registrating additions to SOL2 state
void Script::RegisterBindings(sol::state& state) {
    // 1. Register Object usertype
    state.new_usertype<Object>("Object",
        "posX",
        sol::property(
            &Object::GetPosX, &Object::SetPosX
        ),
        "posY",
        sol::property(
            &Object::GetPosY, &Object::SetPosY
        ),
        "height",
        sol::property(
            &Object::GetHeight, &Object::SetHeight
        ),
        "width",
        sol::property(
            &Object::GetWidth, &Object::SetWidth
        ),
        "path",
        sol::property(
            &Object::GetPath, &Object::SetPath
        ),
        "hasTag", &Object::HasTag,
        "addTag", &Object::AddTag,
        "removeTag", &Object::RemoveTag
    );

    // 2. Registrating DIM (dimension) usertype
    state.new_usertype<DIM>("DIM",
        "width",
        sol::readonly(
            &DIM::GetWidth
        ),
        "height",
        sol::readonly(
            &DIM::GetHeight
        ),
        "addObject",
        &DIM::AddObject
    );
    
    // 3. Register AxisAlignedBoundingBox usertype (hitbox)
    state.new_usertype<AxisAlignedBoundingBox>("AxisAlignedBoundingBox",
        "lowerLeftX",
        sol::readonly(
            &AxisAlignedBoundingBox::GetLowerLeftX
        ),
        "lowerLeftY",
        sol::readonly(
            &AxisAlignedBoundingBox::GetLowerLeftY
        ),
        "upperRightX",
        sol::readonly(
            &AxisAlignedBoundingBox::GetUpperRightX
        ),
        "upperRightY",
        sol::readonly(
            &AxisAlignedBoundingBox::GetUpperRightY
        )
    );

    // 4. Registrating key scancodes
    for (const auto& [name, code] : keyMap) {
        state["KEY_" + name] = code;
    }
    
    // 5. Registrating check the keypress function
    state.set_function("isKeyPressed", [](SDL_Scancode scancode) {
        const bool* keyboardState = SDL_GetKeyboardState(nullptr);
        return keyboardState[scancode] != 0;
    });

    // 6. Registrating currDIM (current dim) funtions
    state.set_function("getCurrDIM", &DIM::GetCurrDIM);
    state.set_function("setCurrDIM", &DIM::SetCurrDIM);

    // 7. Registrating objects' vector functions
    state.set_function("getObjects", []() -> std::vector<std::shared_ptr<Object>> {
        return DIM::GetCurrDIM().GetObjects();
    });
    state.set_function("addObject", [](float posX, float posY, float height, float width, std::vector<std::string> tags, const char * path, AxisAlignedBoundingBox hitbox) {
        DIM::GetCurrDIM().AddObject(posX, posY, height, width, tags, path, hitbox);
    });

}

// A set of static variables that are used to work with the tick system
static float tickAccumulator = 0.0f;
static const int TICKS_PER_SECOND = 60;
static const float tickRate = 1.0f / (float)TICKS_PER_SECOND;
static Uint64 lastTickTime = 0;

// A method that runs .lua scripts every tick (you can change the tickrate)
// Before running this method, you need to initialize scripts
void Script::Run() {
    // 1. Get the permormance frequency once
    static Uint64 freq = SDL_GetPerformanceFrequency(); // how many counts per second
    Uint64 currTime = SDL_GetPerformanceCounter(); // in perfotmance counter units
    
    // 2. Initialize lastTickTime and accumulator on the first call
    if (lastTickTime == 0) {
        lastTickTime = currTime;
        tickAccumulator = 0.0f;
    }

    // 3. Calculate time delta since last tick in seconds
    float deltaTime = (currTime - lastTickTime) / (float)freq;
    // 4. Accumulate delta time will be used to determine how many ticks to run
    tickAccumulator += deltaTime;

    // 5. Count how many full ticks needs to process based on accumulated time
    int ticksToProcess = 0;
    while (tickAccumulator >= tickRate) {
        tickAccumulator -= tickRate;
        ticksToProcess++;
    }

    // 6. Run the logic scripts as many times as calculated
    for (int i = 0; i < ticksToProcess; i++) {
        static Uint64 lastTime = SDL_GetPerformanceCounter();
        Uint64 currentTime = SDL_GetPerformanceCounter();
        float tickDt = (currentTime - lastTime) / (float)SDL_GetPerformanceFrequency();
        lastTime = currentTime;

        SDL_PumpEvents();

        for (std::shared_ptr<sol::state> &state : states) {
            auto update = (*state)["update"];
            if (update.valid()) {
                update(tickDt);
            }
        }
    }

    // 7. Save current time as last tick time
    lastTickTime = currTime;
}

void Script::Clear() {
    states.clear();
}
