//
// Created by david on 1/18/2017.
//

#include "Menu.hpp"
#include "GameStates/IState.h"

void Menu::draw(sf::RenderWindow &window, std::vector<sf::String> txt) {
    mid = sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2);
    int btn = 0;
    sf::Font font;
    font.loadFromFile("./assets/font.ttf");
    for (auto &t : txt) {
        sf::Text text(t, font);
        text.setPosition(mid.x, mid.y + btn * 32);
        window.draw(text);
        btn++;
    }
}

void Menu::input(sf::Vector2i mouse, std::vector<std::function<void(void)>> actions) {
    int btn = 0;
    std::cout << mouse.x<< " - " << mouse.y << " \n";
    std::cout << mid.x<< " - " << mid.y << " \n\n";
    for (auto &b: actions) {
        if (mid.x <= mouse.x &&
            mid.x + 5 * 32 >= mouse.x &&
            mid.y + btn * 32 <= mouse.y &&
            mid.y + (btn + 1) * 32 >= mouse.y) {
            b();
        }
        btn++;
    }
}
