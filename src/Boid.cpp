//
// Created by hassanh on 6/19/2026.
//

#include "Boid.h"

#include "Game.h"

Boid::Boid(int boidId, sf::Vector2f startPosition, sf::Vector2f startVelocity)
{
    m_id = boidId;
    m_position = startPosition;
    m_velocity = startVelocity;
}

void Boid::Update(float deltaTime, float close_dx, float close_dy)
{
    m_velocity.x += close_dx * Game::AVOID_FACTOR;
    m_velocity.y += close_dy * Game::AVOID_FACTOR;
    
    // Majestic turning
    if (m_position.x < Game::EDGE_MARGIN)
    {
        const auto turnFactorRatio = (Game::EDGE_MARGIN - m_position.x) / Game::EDGE_MARGIN ;
        m_velocity.x += Game::TURN_FACTOR * turnFactorRatio;
    }
    else if (m_position.x > Game::WINDOW_WIDTH - Game::EDGE_MARGIN)
    {
        const auto turnFactorRatio = (Game::WINDOW_WIDTH - m_position.x) / Game::EDGE_MARGIN ;
        m_velocity.x -= Game::TURN_FACTOR * turnFactorRatio;
    }
    
    if (m_position.y < Game::EDGE_MARGIN)
    {
        const auto turnFactorRatio = (Game::EDGE_MARGIN - m_position.y) / Game::EDGE_MARGIN ;
        m_velocity.y += Game::TURN_FACTOR * turnFactorRatio;
    }
    
    if (m_position.y > Game::WINDOW_HEIGHT - Game::EDGE_MARGIN)
    {
        const auto turnFactorRatio = (Game::WINDOW_HEIGHT - m_position.y) / Game::EDGE_MARGIN ;
        m_velocity.y -= Game::TURN_FACTOR * turnFactorRatio;
    }

    // Failsafe to keep boids in window
    sf::Vector2f targetNewPosition = m_position + m_velocity * deltaTime;
    if (targetNewPosition.x - RADIUS <= 0 && m_velocity.x < 0 ||
        targetNewPosition.x + RADIUS >= Game::WINDOW_WIDTH && m_velocity.x > 0)
    {
       m_velocity.x = -m_velocity.x;
    }
    if (targetNewPosition.y - RADIUS <= 0 && m_velocity.y < 0 ||
        targetNewPosition.y + RADIUS >= Game::WINDOW_HEIGHT && m_velocity.y > 0)
    {
        m_velocity.y = -m_velocity.y;
    }
    
    m_velocity.x = std::clamp(m_velocity.x, static_cast<float>(-Game::BOID_MAX_SPEED), static_cast<float>(Game::BOID_MAX_SPEED));
    m_velocity.y = std::clamp(m_velocity.y, static_cast<float>(-Game::BOID_MAX_SPEED), static_cast<float>(Game::BOID_MAX_SPEED));
    
    m_position += m_velocity * deltaTime;
}

bool Boid::operator==(const Boid &otherBoid) const
{
    return m_id == otherBoid.m_id;
}

