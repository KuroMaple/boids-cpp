#pragma once



#include <vector>
#include "Boid.h"
#include "../config/GameConfig.h"
#include "SFML/System/Vector2.hpp"



struct AABB
{
    sf::Vector2f m_center;
    float m_halfWidth;
    float m_halfHeight;

    AABB(sf::Vector2f center, float halfWidth, float halfHeight);
    [[nodiscard]] bool ContainsPoint(sf::Vector2f point) const;
    bool IntersectsAABB(const AABB & other) const;
};

struct QuadTreeElement
{
    sf::Vector2f m_position;
    const Boid* m_boidPointer;

};
struct QuadTree
{

    AABB m_boundary;
    int m_capacity = GameConfig::QUAD_TREE_CAPACITY;
    bool m_divided = false;

    std::vector<QuadTreeElement> m_quadTreeBoids;

    std::unique_ptr<QuadTree> topLeft;
    std::unique_ptr<QuadTree> topRight;
    std::unique_ptr<QuadTree> bottomLeft;
    std::unique_ptr<QuadTree> bottomRight;

    explicit QuadTree(AABB boundary);

    bool Insert(const Boid& boid);
    void Subdivide();
    std::vector<const Boid*> QueryRange(AABB range);
};