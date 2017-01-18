//
// Created by david on 11/16/2016.
//

#include <SFML/Graphics.hpp>
#include "Game.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "WaveForms");
    // Game application class
    window.setFramerateLimit(60);
    Game waveForms(window);
    return 0;
}