//
// Created by hassanh on 6/18/2026.
//

#include "Game.h"

void Game::BeginPlay()
{
    if (m_window.isOpen()) return;
    
    m_window.create(sf::VideoMode( { WINDOW_WIDTH, WINDOW_HEIGHT } ), WINDOW_TITLE );
    m_window.setFramerateLimit(FPS);
    
    Boid testBoid = Boid(sf::Vector2f(100,100), sf::Vector2f(1,0));
    m_boidsVector.push_back(testBoid);
    GameLoop();
}

void Game::GameLoop()
{
    while (m_window.isOpen())
    {
        float deltaTime = m_clock.getElapsedTime().asSeconds();

        
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
        boid.Update(deltaTime);
    }
}

void Game::Render()
{
    m_window.clear();
    m_renderer.Draw(m_boidsVector, m_window);
    m_window.display();
}

