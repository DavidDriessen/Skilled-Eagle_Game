//
// Created by david on 11/16/2016.
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Character.hpp"

int main()
{

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    Character c{sf::Vector2f{0,400}, 0.1, 0.2, 80};

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        c.input(event);
        c.update(sf::milliseconds(0));

        window.clear();
        c.draw(window);
        window.display();
    }

    return 0;
}