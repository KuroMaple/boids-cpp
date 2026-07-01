//
// Created by Hassan Hashmi on 2026-06-27.
//

#include "QuadTree.h"

#include "SFML/Window/Keyboard.hpp"

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


    return point.x <= max.x &&
           point.y <= max.y &&
           point.x >= min.x &&
           point.y >= min.y;
}

bool AABB::IntersectsAABB(const AABB& other) const
{
    auto currentBottomLeft = sf::Vector2f(m_center.x - m_halfWidth, m_center.y + m_halfHeight);
    auto currentTopRight = sf::Vector2f(m_center.x + m_halfWidth, m_center.y - m_halfHeight);

    auto otherBottomLeft = sf::Vector2f(other.m_center.x - other.m_halfWidth, other.m_center.y + other.m_halfHeight);
    auto otherTopRight = sf::Vector2f(other.m_center.x + other.m_halfWidth, other.m_center.y - other.m_halfHeight);

    return currentBottomLeft.x < otherTopRight.x &&
            otherBottomLeft.x < currentTopRight.x &&
            currentBottomLeft.y > otherTopRight.y &&
            otherBottomLeft.y > currentTopRight.y;
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

    if (topLeft->Insert(boid)) return true;
    if (topRight->Insert(boid)) return true;
    if (bottomLeft->Insert(boid)) return true;
    if (bottomRight->Insert(boid)) return true;

    return false;
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

void QuadTree::QueryRange(AABB range, std::vector<const Boid*>& foundBoids)
{
    if (!m_boundary.IntersectsAABB(range)) return;

    for (auto& [m_position, m_boidPointer]: m_quadTreeBoids)
    {
        if (range.ContainsPoint(m_position))
        {
            foundBoids.push_back(m_boidPointer);
        }
    }

    if (m_divided)
    {
        topLeft->QueryRange(range, foundBoids);
        topRight->QueryRange(range, foundBoids);
        bottomLeft->QueryRange(range, foundBoids);
        bottomRight->QueryRange(range, foundBoids);
    }
}

void QuadTree::ClearRootTree()
{
    m_quadTreeBoids.clear();
    if (m_divided)
    {
        topLeft.reset();
        topRight.reset();
        bottomLeft.reset();
        bottomRight.reset();
        m_divided = false;
    }
}

