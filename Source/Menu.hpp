//
// Created by david on 1/18/2017.
//

#ifndef SKILLED_EAGLE_GAME_MENU_HPP
#define SKILLED_EAGLE_GAME_MENU_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>


class Menu {
    sf::Vector2i mid;
public:
    void draw(sf::RenderWindow &window, std::vector<sf::String> txt);

    void input(sf::Vector2i mouse, std::vector<std::function<void(void)>> btn);
};


#endif //SKILLED_EAGLE_GAME_MENU_HPP
