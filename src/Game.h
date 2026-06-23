//
// Created by hassanh on 6/18/2026.
//

#ifndef CMAKESFMLPROJECT_GAME_H
#define CMAKESFMLPROJECT_GAME_H
#include <random>
#include <SFML/Graphics.hpp>

#include "Boid.h"
#include "Renderer.h"

class Game
{
public:
    inline const static std::string WINDOW_TITLE = "Boids CPP";
    static constexpr int WINDOW_WIDTH = 1400;
    static constexpr int WINDOW_HEIGHT = 1200;
    static constexpr int FPS = 60;
    static constexpr int BOIDS_COUNT = 100;
    static constexpr int BOID_MAX_SPEED = 200;
    static constexpr auto BOID_VELOCITY = sf::Vector2f(100, 100);
    static constexpr int EDGE_MARGIN = 100;
    static constexpr float TURN_FACTOR = 10;
    static constexpr float PROTECTED_RANGE = 60;
    static constexpr float AVOID_FACTOR = 0.03;
    static constexpr float VISUAL_RANGE = 240;
    static constexpr float MATCHING_FACTOR = 0.02;
    static constexpr float BOID_MIN_SPEED = 200;
    static constexpr float CENTERING_FACTOR = 0.0005;
    
    void BeginPlay();
    void GameLoop();
    void Update(float deltaTime);
    void Render();

private:
    sf::RenderWindow m_window; 
    sf::Clock m_clock;
    std::vector<Boid> m_boidsVector;
    Renderer m_renderer;
    std::mt19937 m_rng;
    std::uniform_int_distribution<> m_distributionX;
    std::uniform_int_distribution<> m_distributionY;
    std::uniform_real_distribution<> m_distributionAngle;

    void SpawnBoids();
    void InitializeRandomEngine();
};


#endif //CMAKESFMLPROJECT_GAME_H