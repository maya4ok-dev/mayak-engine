#pragma once

#include "logger.hpp"
#include <sol/state.hpp>

namespace engine {

class Scripting {
    sol::state state;

public:
    Scripting();

    // bind usertypes
    template<typename Usertype, typename... Args>
    sol::usertype<Usertype> bind(std::string_view name, Args&&... args) {
        auto type = state.new_usertype<Usertype>(name.data(), std::forward<Args>(args)...);
        if (!state[name.data()].valid())
            mlogger.setLevel(error) << "[scripting] " << name.data() << " is invalid" << mayak::logger::core::flush;
        return type;
    }

    // run scripts
    void operator()(double dt);
};

} // namespace engine 
