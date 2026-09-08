#pragma once

#include <sol/state.hpp>

namespace engine {

class Scripting {
    sol::state state;

public:
    Scripting();

    // bind some usertype
    template<typename Usertype, typename Bind>
    void bind(Bind& bind);

    // run scripts
    void operator()(double dt);
};

} // namespace engine 
