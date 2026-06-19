//
// Created by hassanh on 6/19/2026.
//

#include "Boid.h"
Boid::Boid(sf::Vector2f startPosition, sf::Vector2f startVelocity)
{
    m_position = startPosition;
    m_velocity = startVelocity;
}

void Boid::Update(float deltaTime, sf::Vector2f worldBounds)
{
    sf::Vector2f targetNewPosition = m_position + m_velocity * deltaTime;
    if (targetNewPosition.x - RADIUS <= 0 || targetNewPosition.x + RADIUS >= worldBounds.x)
    {
       m_velocity.x = -m_velocity.x; 
    }
    if (targetNewPosition.y - RADIUS <= 0 || targetNewPosition.y + RADIUS >= worldBounds.y)
    {
        m_velocity.y = -m_velocity.y;
    }
    m_position += m_velocity * deltaTime;
}

