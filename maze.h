#ifndef MAZE_H
#define MAZE_H

#include <SFML/Graphics.hpp>

class Maze : public sf::Drawable
{
public:
    Maze(sf::RenderWindow &_window);
    ~Maze();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void initialize(int width,int height, sf::Texture wall, sf::Texture path);
    void update(sf::Time deltaTime);
private:
    static const float SCALE = 0.125f;
    void init_array();
    void maze_generator(int index, int backtrack_x[], int backtrack_y[], int x, int y, int visited);
    int is_closed(int x, int y);

    std::vector<std::vector<sf::Sprite*> > spriteArray;
    sf::RenderWindow * window;
    int width;
    int height;
    int CELL;
    sf::Texture pathTexture;
    sf::Texture wallTexture;
};

#endif // MAZE_H
