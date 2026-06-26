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
    static constexpr int WINDOW_WIDTH = 1000;
    static constexpr int WINDOW_HEIGHT = 700;
    static constexpr int FPS = 60;
    static constexpr int BOID_MAX_SPEED = 200;
    static constexpr auto BOID_VELOCITY = sf::Vector2f(100, 100);
    static constexpr int EDGE_MARGIN = 300;
    static constexpr float AVOID_FACTOR = 0.03;
    static constexpr float VISUAL_RANGE = 240;
    static constexpr float MATCHING_FACTOR = 0.02;
    static constexpr float BOID_MIN_SPEED = 200;
    static constexpr float CENTERING_FACTOR = 0.0005;


    // Commonly Tuned Parameters
    static constexpr int BOIDS_COUNT = 2000;
    static constexpr float TURN_FACTOR = 10;
    static constexpr float PROTECTED_RANGE = 60;
};
#endif //BOIDSCPP_GAMECONFIG_H