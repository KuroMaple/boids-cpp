//
// Created by hassanh on 6/19/2026.
//

#include "Boid.h"

#include "../config/GameConfig.h"
#include "../controller/Game.h"

Boid::Boid(int boidId, sf::Vector2f startPosition, sf::Vector2f startVelocity)
{
    m_id = boidId;
    m_position = startPosition;
    m_velocity = startVelocity;
}

void Boid::Update(float deltaTime, float closeDx, float closeDy,
    int neighbourCount, float xNeighbourVelocityAvg, float yNeighbourVelocityAvg, float xPositionAvg, float yPositionAvg)
{
    // Seperation
    m_velocity.x += closeDx * GameConfig::AVOID_FACTOR;
    m_velocity.y += closeDy * GameConfig::AVOID_FACTOR;

    // Alignment
    if (neighbourCount > 0)
    {
        m_velocity.x += (xNeighbourVelocityAvg - m_velocity.x) * GameConfig::MATCHING_FACTOR;
        m_velocity.y += (yNeighbourVelocityAvg - m_velocity.y) * GameConfig::MATCHING_FACTOR;
    }

    // Cohesion
    if (neighbourCount > 0)
    {
        m_velocity.x += (xPositionAvg - m_velocity.x) * GameConfig::CENTERING_FACTOR;
        m_velocity.y += (yPositionAvg - m_velocity.y) * GameConfig::CENTERING_FACTOR;
    }

    // Speed tuning
    auto currentSpeed = std::sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);
    if (currentSpeed > GameConfig::BOID_MAX_SPEED)
    {
        m_velocity.x = (m_velocity.x / currentSpeed) * GameConfig::BOID_MAX_SPEED;
        m_velocity.y = (m_velocity.y / currentSpeed) * GameConfig::BOID_MAX_SPEED;
    }
    else if (currentSpeed < GameConfig::BOID_MIN_SPEED)
    {
        m_velocity.x = (m_velocity.x / currentSpeed) * GameConfig::BOID_MIN_SPEED;
        m_velocity.y = (m_velocity.y / currentSpeed) * GameConfig::BOID_MIN_SPEED;
    }
    
    // Turning away from edges
    if (m_position.x < GameConfig::EDGE_MARGIN)
    {
        m_velocity.x += GameConfig::TURN_FACTOR ;
    }
    else if (m_position.x > GameConfig::WINDOW_WIDTH - GameConfig::EDGE_MARGIN)
    {
        m_velocity.x -= GameConfig::TURN_FACTOR ;
    }
    
    if (m_position.y < GameConfig::EDGE_MARGIN)
    {
        m_velocity.y += GameConfig::TURN_FACTOR ;
    }
    
    if (m_position.y > GameConfig::WINDOW_HEIGHT - GameConfig::EDGE_MARGIN)
    {
        m_velocity.y -= GameConfig::TURN_FACTOR ;
    }

    m_velocity.x = std::clamp(m_velocity.x, static_cast<float>(-GameConfig::BOID_MAX_SPEED), static_cast<float>(GameConfig::BOID_MAX_SPEED));
    m_velocity.y = std::clamp(m_velocity.y, static_cast<float>(-GameConfig::BOID_MAX_SPEED), static_cast<float>(GameConfig::BOID_MAX_SPEED));

    m_position += m_velocity * deltaTime;
}

bool Boid::operator==(const Boid &otherBoid) const
{
    return m_id == otherBoid.m_id;
}

