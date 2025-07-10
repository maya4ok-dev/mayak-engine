file(GLOB GAME_SOURCES "src/*.cpp")

add_executable(mayak-game ${GAME_SOURCES})

target_include_directories(mayak-game PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(mayak-game PRIVATE mayak-engine)