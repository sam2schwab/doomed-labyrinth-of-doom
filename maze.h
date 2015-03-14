#ifndef MAZE_H
#define MAZE_H

#include <SFML/Graphics.hpp>

class Maze : public sf::Drawable
{
public:
    Maze();
    ~Maze();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void initialize(int width,int height, sf::Texture wall, sf::Texture path);
    void update(sf::Time deltaTime);
};

#endif // MAZE_H
