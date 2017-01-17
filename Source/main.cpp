//
// Created by david on 11/16/2016.
//

#include <SFML/Graphics.hpp>
#include "Game.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    // Game application class
    Game waveForms(window);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Game update method
        waveForms.update();
        // Game draw method
        waveForms.draw();
    }

    return 0;
}