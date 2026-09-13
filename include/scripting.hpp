#pragma once

#include "logger.hpp"
#include <sol/state.hpp>
#include <utility>

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

    template<typename... Args>
    void bind(Args&&... args) {
        state.set(std::forward<Args>(args)...);
    }

    sol::table add_table(std::string_view name) {
        return state.create_named_table(std::string(name));
    }

    sol::table add_table() {
        return state.create_table();
    }

    // run scripts
    void operator()(double dt);
};

} // namespace engine 
