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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            c.move(sf::Vector2f(-c.getSpeed(), 0));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            c.move(sf::Vector2f(c.getSpeed(), 0));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            c.setJumping(true);
        }


        window.clear();
        c.update(window);
        window.display();
    }

    return 0;
}