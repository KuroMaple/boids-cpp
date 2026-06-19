//
// Created by hassanh on 6/19/2026.
//

#include "Renderer.h"
Renderer::Renderer()
{
    m_shape.setPointCount(3);
    m_shape.setPoint(0, sf::Vector2f(0, 0));
    m_shape.setPoint(1, sf::Vector2f(0, 10));
    m_shape.setPoint(2, sf::Vector2f(25, 5));
    m_shape.setOutlineColor(sf::Color::Green);
    m_shape.setOutlineThickness(5);
}

void Renderer::Draw(std::vector<Boid> boidsVector, sf::RenderWindow &gameWindow)
{
    for (const Boid& boid : boidsVector)
    {
        m_shape.setPosition(boid.GetPosition());
        gameWindow.draw(m_shape);
    }
}
