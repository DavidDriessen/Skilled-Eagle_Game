//
// Created by david on 11/16/2016.
//

#include <SFML/Graphics.hpp>
#include "Game.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "WaveForms");
    // Game application class
    Game waveForms(window);
    return 0;
}