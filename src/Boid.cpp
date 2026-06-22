//
// Created by hassanh on 6/19/2026.
//

#include "Boid.h"

#include "Game.h"

Boid::Boid(sf::Vector2f startPosition, sf::Vector2f startVelocity)
{
    m_position = startPosition;
    m_velocity = startVelocity;
}

void Boid::Update(float deltaTime, sf::Vector2f worldBounds)
{
    sf::Vector2f targetNewPosition = m_position + m_velocity * deltaTime;
    
    if (m_position.x < Game::EDGE_MARGIN)
    {
        const auto turnFactorRatio = (Game::EDGE_MARGIN - m_position.x) / Game::EDGE_MARGIN ;
        m_velocity.x += Game::TURN_FACTOR * turnFactorRatio;
    }
    if (m_position.y < Game::EDGE_MARGIN)
    {
        const auto turnFactorRatio = (Game::EDGE_MARGIN - m_position.y) / Game::EDGE_MARGIN ;
        m_velocity.y += Game::TURN_FACTOR * turnFactorRatio;
    }
    if (m_position.x > worldBounds.x - Game::EDGE_MARGIN)
    {
        const auto turnFactorRatio = (worldBounds.x - m_position.x) / Game::EDGE_MARGIN ;
        m_velocity.x -= Game::TURN_FACTOR * turnFactorRatio;
    }
    if (m_position.y > worldBounds.y - Game::EDGE_MARGIN)
    {
        const auto turnFactorRatio = (worldBounds.y - m_position.y) / Game::EDGE_MARGIN ;
        m_velocity.y -= Game::TURN_FACTOR * turnFactorRatio;
    }

    // Failsafes to keep boids in window
    if (targetNewPosition.x - RADIUS <= 0 && m_velocity.x < 0 ||
        targetNewPosition.x + RADIUS >= worldBounds.x && m_velocity.x > 0)
    {
       m_velocity.x = -m_velocity.x;
    }
    if (targetNewPosition.y - RADIUS <= 0 && m_velocity.y < 0 ||
        targetNewPosition.y + RADIUS >= worldBounds.y && m_velocity.y > 0)
    {
        m_velocity.y = -m_velocity.y;
    }

    m_velocity.x = std::clamp(m_velocity.x, static_cast<float>(-Game::BOID_MAX_SPEED), static_cast<float>(Game::BOID_MAX_SPEED));
    m_velocity.y = std::clamp(m_velocity.y, static_cast<float>(-Game::BOID_MAX_SPEED), static_cast<float>(Game::BOID_MAX_SPEED));
    
    m_position += m_velocity * deltaTime;
}

