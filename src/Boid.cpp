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
    m_position += m_velocity * deltaTime;
}

