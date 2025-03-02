cmake_minimum_required(VERSION 3.10) # Set minimum required CMake version
project(2D_ENGINE) # Define the project name

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define source paths
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib)
set(SCRIPTS_DIR ${CMAKE_SOURCE_DIR}/scripts)

# Gather all source files
file(GLOB_RECURSE SOURCES ${SRC_DIR}/*.cpp)

# Create executable
add_executable(2D_ENGINE ${SOURCES})

link_directories(${LIB_DIR})
target_link_libraries(2D_ENGINE PRIVATE
    ${LIB_DIR}/liblua.a
    ${LIB_DIR}/libSDL3.dll.a
)

# Include directories
target_include_directories(2D_ENGINE PRIVATE 
    ${SRC_DIR}
    ${SRC_DIR}/engine
    ${SCRIPTS_DIR}
    ${INCLUDE_DIR}/lua
    ${INCLUDE_DIR}/sol
    ${INCLUDE_DIR}
)
