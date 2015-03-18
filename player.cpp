#include "player.h"

const int Player::SCALE = 1;

Player::Player(sf::RenderWindow &_window,sf::Time frameTime)
    : AnimatedSprite(frameTime,true,true),
      window(&_window)
{

}

Player::~Player()
{

}

void Player::move(int int_dir)
{
    if(!*isMoving)
    {
        switch(int_dir)
        {
        case UP:
            setAnimation(walkingAnimationUp);
            break;
        case DOWN:
            setAnimation(walkingAnimationDown);
            break;
        case LEFT:
            setAnimation(walkingAnimationLeft);
            break;
        case RIGHT:
            setAnimation(walkingAnimationRight);
            break;
        }
    }
}

void Player::update(sf::Time deltaTime)
{
    *isMoving?play():stop();
    AnimatedSprite::update(deltaTime);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    AnimatedSprite::draw(target,states);
}

void Player::initialize(sf::Texture _spriteSheet, bool* moving)
{
    isMoving = moving;
    spriteSheet = _spriteSheet;

    walkingAnimationDown.setSpriteSheet(spriteSheet);
    walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect(64, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect( 0, 0, 32, 32));

    walkingAnimationLeft.setSpriteSheet(spriteSheet);
    walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(64, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect( 0, 32, 32, 32));

    walkingAnimationRight.setSpriteSheet(spriteSheet);
    walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect(64, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect( 0, 64, 32, 32));

    walkingAnimationUp.setSpriteSheet(spriteSheet);
    walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
    walkingAnimationUp.addFrame(sf::IntRect(64, 96, 32, 32));
    walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
    walkingAnimationUp.addFrame(sf::IntRect( 0, 96, 32, 32));

    setAnimation(walkingAnimationDown);

    setPosition(window->getSize().x/2 - 16*SCALE, window->getSize().y/2 - 16*SCALE);
    setScale(SCALE,SCALE);
}
