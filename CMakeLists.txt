cmake_minimum_required(VERSION 3.30)
project(mayak-engine)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# lua
file(GLOB LUA_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/lib/lua/*.c")
add_library(lua STATIC ${LUA_SOURCES})
target_include_directories(lua PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/lib/lua" "${CMAKE_CURRENT_SOURCE_DIR}/lib/lua-shim")

# stb
add_library(stb INTERFACE)
target_include_directories(stb INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/lib/stb)

add_subdirectory(lib/sol2)
add_subdirectory(lib/sdl)
add_subdirectory(lib/glm)

# engine
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")
add_library(mayak-engine STATIC ${SOURCES})
target_include_directories(mayak-engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(mayak-engine PUBLIC
    lua
    sol2
    stb
    SDL3::SDL3
    glm
)

target_compile_options(mayak-engine PRIVATE -Wall -Wextra)

# game
add_subdirectory(game)
