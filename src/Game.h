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
    static constexpr int WINDOW_WIDTH = 1500;
    static constexpr int WINDOW_HEIGHT = 1300;
    static constexpr int FPS = 60;
    static constexpr int BOIDS_COUNT = 50;
    static constexpr int BOID_MAX_SPEED = 100;
    static constexpr auto BOID_VELOCITY = sf::Vector2f(100, 100);
    static constexpr int EDGE_MARGIN = 100;
    static constexpr float TURN_FACTOR = 3;
    static constexpr float PROTECTED_RANGE = 80;
    static constexpr float AVOID_FACTOR = 0.05;
    
    inline const static std::string WINDOW_TITLE = "Boids CPP";
    
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