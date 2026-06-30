//
// Created by Hassan Hashmi on 2026-06-26.
//

#ifndef BOIDSCPP_GAMECONFIG_H
#define BOIDSCPP_GAMECONFIG_H
#include <string>

#include "SFML/System/Vector2.hpp"

struct GameConfig
{
    // Static
    inline const static std::string WINDOW_TITLE = "Boids CPP";
    static constexpr int VISIBLE_WINDOW_WIDTH = 1000;
    static constexpr int VISIBLE_WINDOW_HEIGHT = 700;
    static constexpr int FPS = 60;
    static constexpr float TWO_FLOAT = 2.f;
    static constexpr auto BOID_VELOCITY = sf::Vector2f(100, 100);
    static constexpr float TURN_FACTOR = 5;
    static constexpr float PROTECTED_RANGE = 10;
    static constexpr int EDGE_MARGIN = 100;
    static constexpr float AVOID_FACTOR = 0.03;
    static constexpr float VISUAL_RANGE = 40;
    static constexpr float MATCHING_FACTOR = 0.02;
    static constexpr float BOID_MIN_SPEED = 150;
    static constexpr int BOID_MAX_SPEED = 200;
    static constexpr float CENTERING_FACTOR = 0.0005;
    static constexpr size_t QUAD_TREE_CAPACITY = 4;



    // Commonly Tuned Parameters
    static constexpr int SIMULATION_BOUNDARY_BUFFER_WIDTH = VISIBLE_WINDOW_WIDTH * TWO_FLOAT;
    static constexpr int SIMULATION_BOUNDARY_BUFFER_HEIGHT = VISIBLE_WINDOW_HEIGHT * TWO_FLOAT;
    static constexpr int BOIDS_COUNT = 10000;
    static constexpr bool OPTIMIZATION_ACTIVE = true;
};
#endif //BOIDSCPP_GAMECONFIG_H