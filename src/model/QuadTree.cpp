//
// Created by Hassan Hashmi on 2026-06-27.
//

#include "QuadTree.h"

AABB::AABB(sf::Vector2f center, float halfWidth, float halfHeight)
{
    m_center = center;
    m_halfHeight = halfHeight;
    m_halfWidth = halfWidth;
}

bool AABB::ContainsPoint(sf::Vector2f point) const
{
    const auto min = sf::Vector2f(m_center.x - m_halfWidth, m_center.y - m_halfHeight);
    const auto max = sf::Vector2f(m_center.x + m_halfWidth, m_center.y + m_halfHeight);


    return point.x <= max.x && point.y <= max.y && point.x >= min.x && point.y >= min.y;
}

QuadTree::QuadTree(AABB boundary) : m_boundary(boundary)
{
    m_quadTreeBoids.reserve(m_capacity);
}

bool QuadTree::Insert(const Boid& boid)
{
    if (!m_boundary.ContainsPoint(boid.GetPosition())) return false;

    if (m_quadTreeBoids.size() < m_capacity)
    {
        m_quadTreeBoids.emplace_back(QuadTreeElement{ boid.GetPosition(), &boid });
        return true;
    }

    if (!m_divided)
    {
        Subdivide();
    }
    return topLeft->Insert(boid) || topRight->Insert(boid) ||
        bottomLeft->Insert(boid) || bottomRight->Insert(boid);
}

void QuadTree::Subdivide()
{
    const float childHalfHeight = m_boundary.m_halfHeight / GameConfig::TWO_FLOAT;
    const float  childHalfWidth = m_boundary.m_halfWidth / GameConfig::TWO_FLOAT;

    const auto currentBoundaryCenterX = m_boundary.m_center.x;
    const auto currentBoundaryCenterY = m_boundary.m_center.y;

    topLeft = std::make_unique<QuadTree>(
        AABB(
            {currentBoundaryCenterX - childHalfWidth, currentBoundaryCenterY - childHalfHeight},
            childHalfWidth, childHalfHeight));
    topRight = std::make_unique<QuadTree>(
        AABB(
            {currentBoundaryCenterX + childHalfWidth, currentBoundaryCenterY - childHalfHeight},
            childHalfWidth, childHalfHeight));
    bottomLeft = std::make_unique<QuadTree>(
        AABB({currentBoundaryCenterX - childHalfWidth, currentBoundaryCenterY + childHalfHeight},
            childHalfWidth, childHalfHeight));
    bottomRight = std::make_unique<QuadTree>(
        AABB({currentBoundaryCenterX + childHalfWidth, currentBoundaryCenterY + childHalfHeight},
            childHalfWidth, childHalfHeight));

    m_divided = true;
}

