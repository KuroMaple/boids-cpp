//
// Created by hassanh on 6/18/2026.
//

#include "Game.h"
#include <iostream>
#include <random>
#include <numbers>
#include "../config/GameConfig.h"
#include "../model/QuadTree.h"

Game::Game()
:
m_window(
    sf::VideoMode( { GameConfig::VISIBLE_WINDOW_WIDTH, GameConfig::VISIBLE_WINDOW_HEIGHT } ), GameConfig::WINDOW_TITLE
    ),
m_renderer(m_window)
{
    InitializeFontAndText();

    m_foundBoids.reserve(GameConfig::BOIDS_COUNT);

    // Init Quad tree root
    auto windowAABB = AABB(
        {
            GameConfig::VISIBLE_WINDOW_WIDTH,
            GameConfig::VISIBLE_WINDOW_HEIGHT
        },
        GameConfig::VISIBLE_WINDOW_WIDTH + GameConfig::SIMULATION_BOUNDARY_BUFFER_WIDTH ,
        GameConfig::VISIBLE_WINDOW_HEIGHT + GameConfig::SIMULATION_BOUNDARY_BUFFER_HEIGHT
        );
    m_quadTree = std::make_unique<QuadTree>(windowAABB);
}

void Game::BeginPlay()
{
    
    //m_window.create(sf::VideoMode( { GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT } ), GameConfig::WINDOW_TITLE );
    m_window.setFramerateLimit(GameConfig::FPS);
    InitializeRandomEngine();
    SpawnBoids();
    GameLoop();
}

void Game::GameLoop()
{
    m_clock.restart();
    while (m_window.isOpen())
    {
        float deltaTime = m_clock.restart().asSeconds();

        
        while (const std::optional event = m_window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                m_window.close();
            }
        }

        // Custom profiling
        auto frameStart = std::chrono::high_resolution_clock::now();
        Update(deltaTime);
        auto updateEnd = std::chrono::high_resolution_clock::now();
        Render();
        auto frameEnd = std::chrono::high_resolution_clock::now();

        auto updateMs = std::chrono::duration<double, std::milli>(updateEnd - frameStart).count();
        auto renderMs = std::chrono::duration<double, std::milli>(frameEnd - updateEnd).count();
        auto frameMs = std::chrono::duration<double, std::milli>(frameEnd - frameStart).count();
        auto fps = 1000.0 / frameMs;
        std::string optimizeModeText = GameConfig::OPTIMIZATION_ACTIVE ? "ON" : "OFF";

        std::string displayText = "Boids: " + std::to_string(GameConfig::BOIDS_COUNT) + "\n"
                                    + "Update: " + std::to_string(updateMs) + " ms \n"
                                    + "Render: " + std::to_string(renderMs) + " ms \n"
                                    + "Frame: " + std::to_string(frameMs) + " ms \n"
                                    + "FPS: " + std::to_string(fps) + " \n"
                                    + "Optimization: " + optimizeModeText;

        SetText(displayText);
    }
}

void Game::Update(float deltaTime)
{
    if (GameConfig::OPTIMIZATION_ACTIVE)
    {
        // Re-construct Quad tree
        m_quadTree->ClearRootTree();
        for (const Boid& currentBoid : m_boidsVector)
        {
            m_quadTree->Insert(currentBoid);
        }

        // Loop through each Boid and perform the algorithm
        for (auto &currentBoid : m_boidsVector)
        {
            float closeDx = 0;
            float closeDy = 0;

            float xVelocityAvg = 0;
            float yVelocityAvg = 0;
            int neighbouringBoids = 0;

            float xPositionAvg = 0;
            float yPositionAvg = 0;

            const auto& currentBoidPosition = currentBoid.GetPosition();

            // Range Calculations
            const auto visualAABB = AABB(
                currentBoidPosition,
                GameConfig::VISUAL_RANGE / GameConfig::TWO_FLOAT,
                GameConfig::VISUAL_RANGE / GameConfig::TWO_FLOAT);

            m_foundBoids.clear();
            m_quadTree->QueryRange(visualAABB, m_foundBoids);
            for (const auto &otherBoid : m_foundBoids)
            {
                if (otherBoid == &currentBoid) continue;

                const auto& otherBoidPosition = otherBoid->GetPosition();
                const auto& otherBoidVelocity = otherBoid->GetVelocity();

                const float deltaX = currentBoidPosition.x - otherBoidPosition.x;
                const float deltaY = currentBoidPosition.y - otherBoidPosition.y;

                const float distanceSquared = deltaX*deltaX + deltaY*deltaY;

                if (distanceSquared < GameConfig::PROTECTED_RANGE_SQUARED)
                {
                    closeDx += currentBoidPosition.x - otherBoidPosition.x;
                    closeDy += currentBoidPosition.y - otherBoidPosition.y;
                }
                if (distanceSquared < GameConfig::VISUAL_RANGE_SQUARED)
                {
                    xVelocityAvg += otherBoidVelocity.x;
                    yVelocityAvg += otherBoidVelocity.y;

                    xPositionAvg += otherBoidPosition.x;
                    yPositionAvg += otherBoidPosition.y;

                    ++neighbouringBoids;
                }
            }

            if (neighbouringBoids > 0)
            {
                xVelocityAvg /= neighbouringBoids;
                yVelocityAvg /= neighbouringBoids;
                xPositionAvg /= neighbouringBoids;
                yPositionAvg /= neighbouringBoids;
            }

            currentBoid.Update(deltaTime, closeDx, closeDy, neighbouringBoids, xVelocityAvg, yVelocityAvg, xPositionAvg, yPositionAvg);
        }
    }
    else
    {
        for (auto &currentBoid : m_boidsVector)
        {
            m_farthestBoidVector = {
                std::max(currentBoid.GetPosition().x, m_farthestBoidVector.x),
                std::max(currentBoid.GetPosition().y, m_farthestBoidVector.y)
            };
            float closeDx = 0;
            float closeDy = 0;

            float xVelocityAvg = 0;
            float yVelocityAvg = 0;
            int neighbouringBoids = 0;

            float xPositionAvg = 0;
            float yPositionAvg = 0;

            for (auto &otherBoid : m_boidsVector)
            {
                if (otherBoid == currentBoid) continue;

                if (std::abs(currentBoid.GetPosition().x - otherBoid.GetPosition().x) < GameConfig::PROTECTED_RANGE
                    && std::abs(currentBoid.GetPosition().y - otherBoid.GetPosition().y) < GameConfig::PROTECTED_RANGE)
                {
                    closeDx += currentBoid.GetPosition().x - otherBoid.GetPosition().x;
                    closeDy += currentBoid.GetPosition().y - otherBoid.GetPosition().y;
                }

                if (std::abs(currentBoid.GetPosition().x - otherBoid.GetPosition().x) < GameConfig::VISUAL_RANGE
                    && std::abs(currentBoid.GetPosition().y - otherBoid.GetPosition().y) < GameConfig::VISUAL_RANGE)
                {
                    xVelocityAvg += otherBoid.GetVelocity().x;
                    yVelocityAvg += otherBoid.GetVelocity().y;

                    xPositionAvg += otherBoid.GetPosition().x;
                    yPositionAvg += otherBoid.GetPosition().y;

                    ++neighbouringBoids;
                }
            }

            xVelocityAvg /= neighbouringBoids;
            yVelocityAvg /= neighbouringBoids;
            xPositionAvg /= neighbouringBoids;
            yPositionAvg /= neighbouringBoids;

            currentBoid.Update(deltaTime, closeDx, closeDy, neighbouringBoids, xVelocityAvg, yVelocityAvg, xPositionAvg, yPositionAvg);
        }
    }


}

void Game::Render()
{
    m_window.clear(sf::Color(34, 36, 42));
    m_renderer.Draw(m_boidsVector, *m_quadTree);
    m_window.draw(*m_text);
    m_window.display();
}

void Game::SpawnBoids()
{
    for (int i = 0; i < GameConfig::BOIDS_COUNT; ++i)
    {
        auto currentBoid = Boid(
            i + 1,
            {
                static_cast<float>(m_distributionX(m_rng)),
                 static_cast<float>(m_distributionY(m_rng))
            },
            {
                std::cos(static_cast<float>(m_distributionAngle(m_rng))) * GameConfig::BOID_MAX_SPEED,
                std::sin(static_cast<float>(m_distributionAngle(m_rng))) * GameConfig::BOID_MAX_SPEED
            });
        m_boidsVector.push_back(currentBoid);
        
    }
}

void Game::InitializeRandomEngine()
{
    std::random_device randomDevice;
    m_rng.seed(randomDevice());
    m_distributionX = std::uniform_int_distribution<>(0, GameConfig::VISIBLE_WINDOW_WIDTH);
    m_distributionY = std::uniform_int_distribution<>(0, GameConfig::VISIBLE_WINDOW_HEIGHT);
    m_distributionAngle = std::uniform_real_distribution<>(0, 2 * std::numbers::pi);
}

void Game::InitializeFontAndText()
{
    if (!m_font.openFromFile("assets/font/JetBrainsMono-Regular.ttf"))
    {

        std::cout << "ERROR: Font Not Loaded" << std::endl;
        std::cout << std::filesystem::current_path() << '\n';
    }


    m_text = std::make_unique<sf::Text>(m_font);

    m_text->setString("Hello World");
    m_text->setCharacterSize(24);
    m_text->setFillColor(sf::Color::Yellow);
}

void Game::SetText(const std::string& newText) const
{
    m_text->setString(newText);
}

