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
Renderer::Renderer(sf::RenderWindow &gameWindow): m_gameWindow(gameWindow)
{
    m_boidShape.setPointCount(renderConstants::kBoidUnit.size());
    for (std::size_t i = 0; i < renderConstants::kBoidUnit.size(); ++i)
    {
        m_boidShape.setPoint(i, renderConstants::kBoidUnit[i] * Boid::RADIUS);
    }
    m_boidShape.setOrigin({0,0});
    m_boidShape.setFillColor(sf::Color(153, 255, 133));
    m_boidShape.setOutlineColor(sf::Color::White);
    m_boidShape.setOutlineThickness(renderConstants::kOutlineThickness);
}

void Renderer::Draw(const std::vector<Boid>& boidsVector, const QuadTree& quadTreeRoot)
{
    if (GameConfig::OPTIMIZATION_ACTIVE && GameConfig::SHOW_LINES)
    {
        DrawQuadTree(quadTreeRoot);
    }

    for (const Boid& boid : boidsVector)
    {
        const sf::Vector2f boidVelocity = boid.GetVelocity();
        const float noseAngle = std::atan2(boidVelocity.y, boidVelocity.x);

        m_boidShape.setRotation(sf::radians(noseAngle));
        m_boidShape.setPosition(boid.GetPosition());

        m_gameWindow.draw(m_boidShape);

    }
}

void Renderer::DrawQueryRectangle(const sf::Vector2f& position, const sf::Vector2f& size) const
{
    sf::RectangleShape rectangle(size);
    rectangle.setPosition(position);
    rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setOutlineColor(sf::Color::Green);
    rectangle.setOutlineThickness(1.f);
    m_gameWindow.draw(rectangle);
}

void Renderer::DrawQuadTree(const QuadTree& root)
{
    m_rectangleShape.setSize({root.m_boundary.m_halfWidth * 2.f, root.m_boundary.m_halfHeight * 2.f});

    // Top left corner of AABB
    m_rectangleShape.setPosition(
        {
            root.m_boundary.m_center.x - root.m_boundary.m_halfWidth,
            root.m_boundary.m_center.y - root.m_boundary.m_halfHeight
        });

    m_rectangleShape.setOutlineColor(sf::Color(0x00FFFF));
    m_rectangleShape.setOutlineThickness(0.5f);
    m_rectangleShape.setFillColor(sf::Color::Transparent);
    m_gameWindow.draw(m_rectangleShape);

    if (root.topLeft) DrawQuadTree(*root.topLeft);
    if (root.topRight) DrawQuadTree(*root.topRight);
    if (root.bottomLeft) DrawQuadTree(*root.bottomLeft);
    if (root.bottomRight) DrawQuadTree(*root.bottomRight);
}
