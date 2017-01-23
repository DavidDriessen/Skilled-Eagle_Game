//
// Created by david on 1/18/2017.
//

#include "Menu.hpp"
#include "GameStates/IState.h"

Menu::Menu(float width, float height, int start) : width(width), height(height), start(start), selected(start - 1) {

}

void Menu::draw(sf::RenderWindow &window, std::vector<sf::String> txt) {
    int index = 0;
    float btn = -((float) txt.size() / 2.0f);
    sf::Font font;
    font.loadFromFile("./assets/font.ttf");
    mid = sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2);

    sf::RectangleShape shape({width, height});
    shape.setPosition(sf::Vector2f(mid.x - width / 2, mid.y - height / 2));
    shape.setFillColor(sf::Color::Black);
    shape.setOutlineColor(sf::Color::Yellow);
    shape.setOutlineThickness(5);
    window.draw(shape);

    for (auto &t : txt) {
        if (index == selected && index >= start) {
            sf::RectangleShape hover({(float) t.getSize() * 30.0f + 25, btnHeidth + 3});
            hover.setPosition((float) mid.x - (float) t.getSize() / 2.0f * 30.0f - 5, (float) mid.y + btn * btnHeidth);
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
        index++;
    }
}

void Menu::input(sf::Event &event, sf::Vector2i mouse, std::vector<std::function<void(void)>> actions, bool arrows) {
    if ((event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left)) ||
        (event.type == sf::Event::KeyPressed &&
         (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) ||
          ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) &&
           arrows)))) {
        int index = 0;
        for (auto &b: actions) {
            if (index == selected) {
                b();
            }
            index++;
        }
    } else if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        selected--;
        if (selected < start) {
            selected = (int) actions.size() - 1;
        }
    } else if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        selected++;
        if (selected >= actions.size()) {
            selected = start;
        }
    } else if (event.type == sf::Event::MouseMoved) {
        int index = 0;
        selected = -1;
        float btn = -((float) actions.size() / 2.0f);
        for (auto &b: actions) {
            if (mid.x - width / 2 <= mouse.x &&
                mid.x + width / 2 >= mouse.x &&
                mid.y + btn * 60 <= mouse.y &&
                mid.y + (btn + 1) * 60 - 5 >= mouse.y) {
                selected = index;
            }
            btn++;
            index++;
        }
    }
}
