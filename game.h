#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

class Game
{
public:
    Game();
    ~Game();
    int exec();
private:
    sf::Vector2i screenDimensions;
    sf::RenderWindow window;
    sf::Clock frameClock;

    void initialize();
    void loadContent();
    void draw(sf::RenderWindow &window);
    void update(sf::Time deltaTime);

    void manageClosing();
};

#endif // GAME_H
