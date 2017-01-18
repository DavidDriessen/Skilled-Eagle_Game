//
// Created by david on 1/18/2017.
//

#include "Menu.hpp"
#include "GameStates/IState.h"

void Menu::draw(sf::Window &w, std::vector<sf::String> txt) {
    mid = sf::Vector2i(w.getSize().x / 2, w.getSize().y / 2);
    int btn = 0;
    sf::Font font;
    font.loadFromFile("arial.ttf");
    for (auto &t : txt) {
        sf::Text text(t, font);
        text.setPosition(mid.x, mid.y + btn * 32);
    }
}

void Menu::update(float &x, std::vector<std::function<void(void)>> actions) {
    sf::Vector2i mouse(sf::Mouse::getPosition());
    int btn = 0;
    for (auto &b: actions) {
        if (mid.x <= mouse.x &&
            mid.x + 5 * 32 >= mouse.x &&
            mid.y + btn * 32 <= mouse.y &&
            mid.y + (btn + 1) * 32 >= mouse.y) {
            b();
        }
    }
}
