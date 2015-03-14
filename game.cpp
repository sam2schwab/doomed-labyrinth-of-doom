#include "game.h"

Game::Game()
    : screenDimensions(800,600),
      window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Doomed Labyrinth of Doom")
{
    window.setFramerateLimit(60);
}

Game::~Game()
{

}

int Game::exec()
{
    loadContent();
    initialize();

    while (window.isOpen())
    {
        manageClosing();

        //restart the clock and keep the elapsed time stored in frameTime variable
        sf::Time frameTime = frameClock.restart();

        // update game components
        update(frameTime);

        // draw game components
        draw(window);
    }

    return 0;
}

void Game::initialize()
{
    //Create game components here

}

void Game::loadContent()
{
    //Load ressources here

}

void Game::update(sf::Time deltaTime)
{
    //Update game components here

}

void Game::draw(sf::RenderWindow &window)
{
    window.clear(sf::Color::Cyan);
    //Draw game components here
    //example: window.draw(componentName);

    window.display();
}

void Game::manageClosing(){
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        //if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            //window.close();
    }
}
