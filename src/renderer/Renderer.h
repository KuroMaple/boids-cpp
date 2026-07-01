//
// Created by hassanh on 6/19/2026.
//

#ifndef CMAKESFMLPROJECT_RENDERER_H
#define CMAKESFMLPROJECT_RENDERER_H
#include <vector>

#include "../model/Boid.h"
#include "../model/QuadTree.h"
#include "SFML/Graphics/ConvexShape.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"


class Renderer
{
public:
    explicit Renderer(sf::RenderWindow &gameWindow);
    void Draw(const std::vector<Boid>& boidsVector, const QuadTree& quadTreeRoot);

    void DrawQueryRectangle(const sf::Vector2f& position, const sf::Vector2f& size) const;
private:
    sf::ConvexShape m_boidShape;
    sf::RectangleShape m_rectangleShape;
    sf::RenderWindow &m_gameWindow;

    void DrawQuadTree(const QuadTree& root);
};


#endif //CMAKESFMLPROJECT_RENDERER_H