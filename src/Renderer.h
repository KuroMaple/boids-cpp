//
// Created by hassanh on 6/19/2026.
//

#ifndef CMAKESFMLPROJECT_RENDERER_H
#define CMAKESFMLPROJECT_RENDERER_H
#include <vector>

#include "Boid.h"
#include "SFML/Graphics/ConvexShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"


class Renderer
{
public:
    Renderer();
    void Draw(const std::vector<Boid>& boidsVector, sf::RenderWindow& gameWindow);

private:
    sf::ConvexShape m_shape;
};


#endif //CMAKESFMLPROJECT_RENDERER_H