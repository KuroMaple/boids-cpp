//
// Created by hassanh on 6/19/2026.
//

#include "Boid.h"
Boid::Boid(sf::Vector2f startPosition, sf::Vector2f startVelocity)
{
    m_position = startPosition;
    m_velocity = startVelocity;
}

void Boid::Update(float deltaTime)
{
    sf::Vector2f targetNewPosition = m_position + m_velocity * deltaTime;
    if (targetNewPosition.x <= 0 || targetNewPosition.x > 760)
    {
       m_velocity.x = -m_velocity.x; 
    }
    else if (targetNewPosition.y < 0 || targetNewPosition.y > 590)
    {
        m_velocity.y = -m_velocity.y;
    }
    m_position += m_velocity * deltaTime;
}

