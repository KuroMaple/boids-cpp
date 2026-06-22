//
// Created by hassanh on 6/18/2026.
//

#include "Game.h"
#include <random>
#include <numbers>

void Game::BeginPlay()
{
    if (m_window.isOpen()) return;
    
    m_window.create(sf::VideoMode( { WINDOW_WIDTH, WINDOW_HEIGHT } ), WINDOW_TITLE );
    m_window.setFramerateLimit(FPS);
    InitializeRandomEngine();
    SpawnBoids();
    GameLoop();
}

void Game::GameLoop()
{
    m_clock.restart();
    while (m_window.isOpen())
    {
        float deltaTime = m_clock.restart().asSeconds();

        
        while (const std::optional event = m_window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                m_window.close();
            }
        }
        Update(deltaTime);
        Render();
    }
}

void Game::Update(float deltaTime)
{
    for (auto &boid : m_boidsVector)
    {
        boid.Update(deltaTime, { WINDOW_WIDTH, WINDOW_HEIGHT});
    }
}

void Game::Render()
{
    m_window.clear();
    m_renderer.Draw(m_boidsVector, m_window);
    m_window.display();
}

void Game::SpawnBoids()
{
    for (int i = 0; i < BOIDS_COUNT; ++i)
    {
        auto currentBoid = Boid(
            {
                static_cast<float>(m_distributionX(m_rng)),
                 static_cast<float>(m_distributionY(m_rng))
            },
            {
                std::cos(static_cast<float>(m_distributionAngle(m_rng))) * BOID_MAX_SPEED,
                std::sin(static_cast<float>(m_distributionAngle(m_rng))) * BOID_MAX_SPEED
            });
        m_boidsVector.push_back(currentBoid);
        
    }
}

void Game::InitializeRandomEngine()
{
    std::random_device randomDevice;
    m_rng.seed(randomDevice());
    m_distributionX = std::uniform_int_distribution<>(0, WINDOW_WIDTH);
    m_distributionY = std::uniform_int_distribution<>(0, WINDOW_HEIGHT);
    m_distributionAngle = std::uniform_real_distribution<>(0, 2 * std::numbers::pi);
}

