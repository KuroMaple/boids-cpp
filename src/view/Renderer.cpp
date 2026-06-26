//
// Created by hassanh on 6/19/2026.
//

#include "Renderer.h"

namespace renderConstants
{
    constexpr std::array<sf::Vector2f, 4> kBoidUnit = {
        {
            {  1.0f,  0.0f },   
            { -0.6f,  0.5f },   
            { -0.8f,  0.0f },   
            { -0.6f, -0.5f },  
        }};

    constexpr float kOutlineThickness = 1.0f;
}
Renderer::Renderer()
{
    m_shape.setPointCount(renderConstants::kBoidUnit.size());
    for (std::size_t i = 0; i < renderConstants::kBoidUnit.size(); ++i)
    {
        m_shape.setPoint(i, renderConstants::kBoidUnit[i] * Boid::RADIUS);  
    }
    m_shape.setOrigin({0,0});
    m_shape.setFillColor(sf::Color(153, 255, 133));
    m_shape.setOutlineColor(sf::Color::White);
    m_shape.setOutlineThickness(renderConstants::kOutlineThickness);
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
