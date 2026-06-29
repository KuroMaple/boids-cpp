cmake_minimum_required(VERSION 3.28)
project(BoidsCPP LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main src/main.cpp
        src/controller/Game.cpp
        src/controller/Game.h
        src/model/Boid.cpp
        src/model/Boid.h
        src/Renderer/Renderer.cpp
        src/Renderer/Renderer.h
        src/config/GameConfig.h
        src/model/QuadTree.h
        src/model/QuadTree.cpp)

add_custom_command(TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets
)

target_compile_features(main PRIVATE cxx_std_23)
target_link_libraries(main PRIVATE SFML::Graphics)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)
