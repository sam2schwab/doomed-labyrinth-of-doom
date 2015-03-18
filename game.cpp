#include "game.h"
#include <qdebug.h>

Game::Game()
    : screenDimensions(800,600),
      window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Doomed Labyrinth of Doom"/*, sf::Style::Fullscreen*/),
      maze(window),
      player(window,sf::seconds(0.2))
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
        manageEvents();

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

    //ressources for player
    playerTexture.loadFromFile("player.png");
    playerTexture.setSmooth(true);
}

void Game::initialize()
{
    //Create game components here

    //initializing labyrinth
    maze.initialize(20,15,wallTexture,pathTexture);

    //initializing player
    player.initialize(playerTexture, maze.getMoving());
}

void Game::update(sf::Time deltaTime)
{
    //Update game components here

    //updating labyrinth
    maze.update(deltaTime);

    //updating player
    player.update(deltaTime);
}

void Game::draw()
{
    window.clear(sf::Color::Black);
    //Draw game components here
    //example: window.draw(componentName);

    //drawing labyrinth
    window.draw(maze);

    //drawing player
    window.draw(player);

    window.display();
}

void Game::manageEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
        {
            player.move(Player::UP);
            maze.move(Maze::UP);
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
        {
            player.move(Player::RIGHT);
            maze.move(Maze::RIGHT);
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
        {
            player.move(Player::DOWN);
            maze.move(Maze::DOWN);
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
        {
            player.move(Player::LEFT);
            maze.move(Maze::LEFT);
        }
    }
}
