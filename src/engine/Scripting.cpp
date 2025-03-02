// File: ScriptEngine.cpp

#include "Scripting.h"
#include <iostream>
#include <filesystem>
#include <DIM.h>

std::vector<std::string> scripts;
std::vector<std::unique_ptr<sol::state>> states;

// Method to load scripts
void ScriptInit() {
    for (const auto& entry : std::filesystem::directory_iterator("scripts")) {
        scripts.push_back(entry.path().string());
    }
    
    for (const auto& script : scripts) {
        std::unique_ptr<sol::state> state = std::make_unique<sol::state> ();
        state->open_libraries(sol::lib::base, sol::lib::package);
        ScriptReg(*state);
        state->script_file(script);
        states.emplace_back(std::move(state));
    }
}

// Method to register other methods
void ScriptReg(sol::state& state) {
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
        "colorR",
        sol::property(
            &Object::GetColorR, &Object::SetColorR
        ),
        "colorG",
        sol::property(
            &Object::GetColorG, &Object::SetColorG
        ),
        "colorB",
        sol::property(
            &Object::GetColorB, &Object::SetColorB
        ),
        "type",
        sol::property(
            &Object::GetType, &Object::SetType
        )
    );

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

    state.set_function("getCurrDIM", &DIM::GetCurrDIM);
    state.set_function("setCurrDIM", &DIM::SetCurrDIM);
}

// Method to run scripts
void ScriptRun() {
    for(std::unique_ptr<sol::state> &state : states) {
        auto initialize = (*state)["initialize"];
        if (initialize != sol::nil) {
            initialize.get<sol::function>()();
        } else { std::cout << "error: initialize func in script not found!" << std::endl; }
    }
}