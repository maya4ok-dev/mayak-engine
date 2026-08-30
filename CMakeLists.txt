cmake_minimum_required(VERSION 3.30)
project(mayak-engine)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB LUA_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/lib/lua/*.c")
add_library(lua STATIC ${LUA_SOURCES})
target_include_directories(lua PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/lib/lua" "${CMAKE_CURRENT_SOURCE_DIR}/lib/lua-shim")

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_subdirectory(lib/sol2)
add_subdirectory(lib/sdl)
add_subdirectory(lib/glm)

add_library(mayak-engine STATIC ${SOURCES})

# Catch extra errors
target_compile_options(mayak-engine PRIVATE -Wall -Wextra)

# Header-only dependencies + engine
target_include_directories(
    mayak-engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/stb
)

target_link_libraries(mayak-engine PUBLIC
    sol2
    SDL3
    lua
    glm
)

add_subdirectory(game)
