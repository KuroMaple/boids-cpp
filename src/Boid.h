//
// Created by hassanh on 6/19/2026.
//

#ifndef CMAKESFMLPROJECT_BOID_H
#define CMAKESFMLPROJECT_BOID_H
#include <SFML/System/Vector2.hpp> 


class Boid
{
public:
    Boid(int boidID, sf::Vector2f startPosition, sf::Vector2f startVelocity);

    void Update(float deltaTime, float closeDx, float closeDy,
        int neighbourCount, float xNeighbourVelocityAvg, float yNeighbourVelocityAvg,
        float xPositionAvg, float yPositionAvg);
    [[nodiscard]] sf::Vector2f GetPosition() const { return m_position; }
    [[nodiscard]] sf::Vector2f GetVelocity() const { return m_velocity; }

    static constexpr float RADIUS = 20.f;

    bool operator==(const Boid& otherBoid) const;
private:
    sf::Vector2f m_position;
    sf::Vector2f m_velocity;

    int m_id;
};


#endif //CMAKESFMLPROJECT_BOID_H