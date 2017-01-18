//
// Created by david on 1/18/2017.
//

#include "Menu.hpp"
#include "GameStates/IState.h"

void Menu::draw(sf::RenderWindow &window, std::vector<sf::String> txt) {
    float btn = -((float) txt.size() / 2.0f);
    sf::Font font;
    font.loadFromFile("./assets/font.ttf");
    auto mouse = sf::Mouse::getPosition(window);
    mid = sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2);

    sf::RectangleShape shape({width, height});
    shape.setPosition(sf::Vector2f(mid.x - width / 2, mid.y - height / 2));
    shape.setFillColor(sf::Color::Black);
    shape.setOutlineColor(sf::Color::Yellow);
    shape.setOutlineThickness(5);
    window.draw(shape);

    for (auto &t : txt) {
        if (mid.x - width / 2 <= mouse.x &&
            mid.x + width / 2 >= mouse.x &&
            mid.y + btn * 60 <= mouse.y &&
            mid.y + (btn + 1) * 60 - 5 >= mouse.y) {
            sf::RectangleShape hover({(float) t.getSize() * 30.0f + 25, 63});
            hover.setPosition((float) mid.x - (float) t.getSize() / 2.0f * 30.0f - 5, (float) mid.y + btn * 60.0f);
            hover.setFillColor(sf::Color::Black);
            hover.setOutlineColor(sf::Color::Yellow);
            hover.setOutlineThickness(5);
            window.draw(hover);
        }

        sf::Text text(t, font);
        text.setPosition((float) mid.x - (float) t.getSize() / 2.0f * 30.0f, (float) mid.y + btn * 60.0f + 5);
        text.setScale(3, 2);
        text.setStyle(sf::Text::Italic);
        text.setFillColor(sf::Color::Blue);
        window.draw(text);
        btn++;
    }
}

void Menu::input(sf::Vector2i mouse, std::vector<std::function<void(void)>> actions) {
    float btn = -((float) actions.size() / 2.0f);
    for (auto &b: actions) {
        if (mid.x - width / 2 <= mouse.x &&
            mid.x + width / 2 >= mouse.x &&
            mid.y + btn * 60 <= mouse.y &&
            mid.y + (btn + 1) * 60 - 5 >= mouse.y) {
            b();
        }
        btn++;
    }
}

Menu::Menu(float width, float height) : width(width), height(height) {

}
