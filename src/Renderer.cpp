//
// Created by hassanh on 6/19/2026.
//

#include "Renderer.h"

namespace
{
    constexpr std::array<sf::Vector2f, 4> kBoidUnit = {
        {
            {  1.0f,  0.0f },   
            { -0.6f,  0.5f },   
            { -0.8f,  0.0f },   
            { -0.6f, -0.5f },  
        }};

    constexpr float kOutlineThickness = 3.0f;
}
Renderer::Renderer()
{
    m_shape.setPointCount(kBoidUnit.size());
    for (std::size_t i = 0; i < kBoidUnit.size(); ++i)
        m_shape.setPoint(i, kBoidUnit[i] * Boid::RADIUS);  
    m_shape.setOrigin({0,0});
    m_shape.setOutlineColor(sf::Color::Green);
    m_shape.setOutlineThickness(kOutlineThickness);
}

void Renderer::Draw(const std::vector<Boid>& boidsVector, sf::RenderWindow &gameWindow)
{
    for (const Boid& boid : boidsVector)
    {
        sf::Vector2f boidVelocity = boid.GetVelocity();
        float noseAngle = std::atan2(boidVelocity.y, boidVelocity.x);
        
        m_shape.setRotation(sf::radians(noseAngle));
        m_shape.setPosition(boid.GetPosition());
        
        gameWindow.draw(m_shape);
    }
}
