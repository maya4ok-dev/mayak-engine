add_executable(mayak-game src/main.cpp src/enemy.cpp)
target_include_directories(mayak-game PRIVATE include)
target_link_libraries(mayak-game PRIVATE mayak-engine)
