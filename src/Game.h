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
    
    static void BeginPlay();
    void HandleInput();
    void Update();
    void Render();

    sf::RenderWindow GetWindow();
private:
    
    static sf::RenderWindow m_window; 
    static sf::Clock m_clock;
    // sf::ConvexShape m_shape;
};


#endif //CMAKESFMLPROJECT_GAME_H