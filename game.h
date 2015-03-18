#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "maze.h"
#include "player.h"

class Game
{
public:
    Game();
    ~Game();
    int exec();
private:
    //members for ctor
    sf::Vector2i screenDimensions;
    sf::RenderWindow window;
    sf::Clock frameClock;

    //members for labyrinth
    sf::Texture wallTexture;
    sf::Texture pathTexture;
    Maze maze;

    //members for player
    sf::Texture playerTexture;
    Player player;

    void initialize();
    void loadContent();
    void draw();
    void update(sf::Time deltaTime);

    void manageEvents();
};

#endif // GAME_H
