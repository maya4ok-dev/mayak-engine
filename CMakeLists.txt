cmake_minimum_required(VERSION 3.10) # Set minimum required CMake version

set(TARGET_NAME Game)
project(${TARGET_NAME}) # Define the project name

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define source paths
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib)
set(SCRIPTS_DIR ${CMAKE_BINARY_DIR})

# Gather all source files
file(GLOB_RECURSE SOURCES ${SRC_DIR}/*.cpp)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# Create executable
add_executable(${TARGET_NAME} ${SOURCES})

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/scripts ${CMAKE_BINARY_DIR}/bin/scripts
)

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/bin ${CMAKE_BINARY_DIR}/bin
)

target_link_libraries(${TARGET_NAME} PRIVATE
    ${LIB_DIR}/liblua.a
    ${LIB_DIR}/libSDL3.dll.a
)

# Include directories
target_include_directories(${TARGET_NAME} PRIVATE 
    ${SRC_DIR}
    ${SRC_DIR}/engine
    ${SCRIPTS_DIR}
    ${INCLUDE_DIR}/lua
    ${INCLUDE_DIR}/sol
    ${INCLUDE_DIR}
)
