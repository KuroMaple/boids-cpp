//
// Created by hassanh on 6/18/2026.
//

#ifndef CMAKESFMLPROJECT_GAME_H
#define CMAKESFMLPROJECT_GAME_H
#include <random>
#include <SFML/Graphics.hpp>

#include "../model/Boid.h"
#include "../view/Renderer.h"

class Game
{
public:
    Game();
    void BeginPlay();
    void GameLoop();
    void Update(float deltaTime);
    void Render();

private:
    sf::RenderWindow m_window; 
    sf::Clock m_clock;
    std::vector<Boid> m_boidsVector;
    Renderer m_renderer;
    std::mt19937 m_rng;
    std::uniform_int_distribution<> m_distributionX;
    std::uniform_int_distribution<> m_distributionY;
    std::uniform_real_distribution<> m_distributionAngle;
    sf::Font m_font;
    std::unique_ptr<sf::Text> m_text;

    void SpawnBoids();
    void InitializeRandomEngine();
    void InitializeFontAndText();
    void SetText(std::string newText);
};


#endif //CMAKESFMLPROJECT_GAME_H