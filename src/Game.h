//
// Created by hassanh on 6/18/2026.
//

#ifndef CMAKESFMLPROJECT_GAME_H
#define CMAKESFMLPROJECT_GAME_H
#include <SFML/Graphics.hpp>

#include "Boid.h"
#include "Renderer.h"

class Game
{
public:
    const static int WINDOW_WIDTH = 800;
    const static int WINDOW_HEIGHT = 600;
    const static int FPS = 60;
    const static int BOIDS_COUNT = 1;
    inline const static std::string WINDOW_TITLE = "Boids CPP";
    
    void BeginPlay();
    void GameLoop();
    void Update(float deltaTime);
    void Render();

private:
    
    sf::RenderWindow m_window; 
    sf::Clock m_clock;
    std::vector<Boid> m_boidsVector;
    Renderer m_renderer;
};


#endif //CMAKESFMLPROJECT_GAME_H