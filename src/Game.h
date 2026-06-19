//
// Created by hassanh on 6/18/2026.
//

#ifndef CMAKESFMLPROJECT_GAME_H
#define CMAKESFMLPROJECT_GAME_H
#include <SFML/Graphics.hpp>

class Game
{
public:
    const static int WINDOW_WIDTH = 800;
    const static int WINDOW_HEIGHT = 600;
    
    void BeginPlay();
    void GameLoop();
    void Update();
    void Render();

private:
    
    sf::RenderWindow m_window; 
    sf::Clock m_clock;
    sf::ConvexShape m_shape = sf::ConvexShape();
};


#endif //CMAKESFMLPROJECT_GAME_H