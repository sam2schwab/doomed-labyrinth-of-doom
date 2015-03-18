#include "game.h"

Game::Game()
    : screenDimensions(800,600),
      window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Doomed Labyrinth of Doom"),
      maze(window)
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
        draw();
    }

    return 0;
}

void Game::loadContent()
{
    //Load ressources here

    //ressources for labyrinth
    wallTexture.loadFromFile("wall.png");
    wallTexture.setSmooth(true);
    pathTexture.loadFromFile("path.png");
    pathTexture.setSmooth(true);
}

void Game::initialize()
{
    //Create game components here

    //initializing labyrinth
    maze.initialize(20,15,wallTexture,pathTexture);

}

void Game::update(sf::Time deltaTime)
{
    //Update game components here

    //updating labyrinth
    maze.update(deltaTime);
}

void Game::draw()
{
    window.clear(sf::Color::Cyan);
    //Draw game components here
    //example: window.draw(componentName);

    //drawing labyrinth
    window.draw(maze);

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
