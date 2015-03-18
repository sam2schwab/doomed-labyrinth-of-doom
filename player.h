#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "AnimatedSprite.h"
#include "Animation.h"

class Player : public AnimatedSprite
{
public:
    Player(sf::RenderWindow &_window, sf::Time frameTime = sf::seconds(0.2f));
    ~Player();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void initialize(sf::Texture _spriteSheet, bool *moving);
    void update(sf::Time deltaTime);
    void move(int int_dir);

    static const int UP = 0;
    static const int RIGHT = 1;
    static const int LEFT = 2;
    static const int DOWN = 3;
private:
    static const int SCALE;
    sf::RenderWindow * window;
    const bool * isMoving;
    sf::Texture spriteSheet;
    Animation walkingAnimationDown;
    Animation walkingAnimationLeft;
    Animation walkingAnimationRight;
    Animation walkingAnimationUp;
};

#endif // PLAYER_H
