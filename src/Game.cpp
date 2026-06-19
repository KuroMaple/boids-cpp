//
// Created by hassanh on 6/18/2026.
//

#include "Game.h"

sf::RenderWindow Game::m_window;

void Game::BeginPlay()
{
    if (m_window.isOpen()) return;
    
    m_window.create(sf::VideoMode( { WINDOW_WIDTH, WINDOW_HEIGHT } ), "Boids CPP" );

    while (m_window.isOpen())
    {
        while (const std::optional event = m_window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                m_window.close();
            }
        }
        
    }
    
    // bird->setPointCount(3);
    // bird->setPoint(0, sf::Vector2f(0, 0));
    // bird->setPoint(1, sf::Vector2f(0, 10));
    // bird->setPoint(2, sf::Vector2f(25, 5));
    // bird->setOutlineColor(sf::Color::Green);
    // bird->setOutlineThickness(5);
    // bird->setPosition( { 100, 100 } );
}

void Game::Update()
{
    // sf::Vector2f oldPosition = bird->getPosition();
    // if (oldPosition.x >= 700) {
    //     oldPosition.x = 0;
    // }
		  //
    // bird->setPosition( { oldPosition.x + 1, oldPosition.y } );
}

void Game::Render()
{
    m_window.clear();
    // m_window.draw(*bird);
    m_window.display();
}

sf::RenderWindow Game::GetWindow()
{
    return std::move(m_window);
}
