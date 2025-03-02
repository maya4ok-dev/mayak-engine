// File: Scripting.h

// #pragma once

#include "sol.hpp"
#include <vector>
#include <string>
#include "DIM.h"

extern std::vector<std::string> scripts;
extern std::vector<std::unique_ptr<sol::state>> states;

// Management methods
void ScriptInit();
void ScriptReg(sol::state& state);
void ScriptRun();