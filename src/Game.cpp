//
// Created by hassanh on 6/18/2026.
//

#include "Game.h"

void Game::BeginPlay()
{
    if (m_window.isOpen()) return;
    
    m_window.create(sf::VideoMode( { WINDOW_WIDTH, WINDOW_HEIGHT } ), "Boids CPP" );
    m_window.setFramerateLimit(60);
    
    m_shape.setPointCount(3);
    m_shape.setPoint(0, sf::Vector2f(0, 0));
    m_shape.setPoint(1, sf::Vector2f(0, 10));
    m_shape.setPoint(2, sf::Vector2f(25, 5));
    m_shape.setOutlineColor(sf::Color::Green);
    m_shape.setOutlineThickness(5);
    m_shape.setPosition( { 100, 100 } );
    
    GameLoop();
}

void Game::GameLoop()
{
    while (m_window.isOpen())
    {
        float timeElapsed = Game::m_clock.getElapsedTime().asSeconds();

        
        while (const std::optional event = m_window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                m_window.close();
            }
        }
        Render();
    }
}

void Game::Update()
{
    // sf::Vector2f oldPosition = m_shape.getPosition();
    // if (oldPosition.x >= 700) {
    //     oldPosition.x = 0;
    // }
		  //
    // m_shape.setPosition( { oldPosition.x + 1, oldPosition.y } );
}

void Game::Render()
{
    m_window.clear();
    m_window.draw(m_shape);
    m_window.display();
}

