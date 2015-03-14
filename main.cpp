//Test Josiane
//test anne-marie
#include "mainwindow.h"
#include "main.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    sf::Vector2i screenDimensions(800,600);
    sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Doomed Labyrinth of Doom");
    window.setFramerateLimit(60);

    LoadContent();
    Initialize();

    //clock counting time between each iteration of the game loop
    sf::Clock frameClock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            //if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                //window.close();
        }

        //restart the clock and keep the elapsed time stored in frameTime variable
        sf::Time frameTime = frameClock.restart();

        // update game components
        Update(frameTime);

        // draw game components
        Draw(window);
    }

    return 0;
}

void Initialize()
{
    //Create game components here

}

void LoadContent()
{
    //Load ressources here

}

void Update(sf::Time deltaTime)
{
    //Update game components here

}

void Draw(sf::RenderWindow &window)
{
    window.clear();
    //Draw game components here
    //example: window.draw(componentName);

    window.display();
}
