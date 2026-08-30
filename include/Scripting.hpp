#include <sol/sol.hpp>
#include <vector>
#include <string>

extern std::vector<std::string> scripts;
extern std::vector<std::shared_ptr<sol::state>> states;

namespace Script {
    void Init();
    void RegisterBindings(sol::state& state);
    void Run();
    void Clear();
}
