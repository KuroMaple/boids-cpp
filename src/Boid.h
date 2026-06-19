//
// Created by hassanh on 6/19/2026.
//

#ifndef CMAKESFMLPROJECT_BOID_H
#define CMAKESFMLPROJECT_BOID_H
#include <SFML/System/Vector2.hpp> 


class Boid
{
public:
    Boid(sf::Vector2f startPosition, sf::Vector2f startVelocity);

    void Update(float deltaTime, sf::Vector2f worldBounds);
    sf::Vector2f GetPosition() const { return m_position; }
    sf::Vector2f GetVelocity() const { return m_velocity; }

    static constexpr float RADIUS = 20.f;
private:
    sf::Vector2f m_position;
    sf::Vector2f m_velocity;
    
};


#endif //CMAKESFMLPROJECT_BOID_H