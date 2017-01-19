//
// Created by david on 1/18/2017.
//

#ifndef SKILLED_EAGLE_GAME_MENU_HPP
#define SKILLED_EAGLE_GAME_MENU_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>


class Menu {
    int selected = -1;
    sf::Vector2i mid;
    float btnHeidth = 60.0f;
    float width, height;
public:
    Menu(float width = 400, float height = 400);

    void draw(sf::RenderWindow &window, std::vector<sf::String> txt);

    void input(sf::Event &event, sf::Vector2i mouse, std::vector<std::function<void(void)>> btn, bool arrows = false);
};


#endif //SKILLED_EAGLE_GAME_MENU_HPP
