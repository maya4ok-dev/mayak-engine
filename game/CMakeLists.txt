add_executable(mayak-game src/main.cpp)

target_include_directories(mayak-game PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(mayak-game PRIVATE mayak-engine)
