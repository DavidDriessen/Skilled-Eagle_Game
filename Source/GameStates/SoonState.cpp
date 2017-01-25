//
// Created by david on 1/25/2017.
//

#include "SoonState.hpp"
#include "../Game.h"

SoonState::SoonState(Game *pGame) {
    game = pGame;
    font.loadFromFile("./assets/font.ttf");
    shape.setSize({500, 150});
    shape.setFillColor(sf::Color::Black);
    shape.setOutlineColor(sf::Color::Yellow);
    shape.setOutlineThickness(5);

    sf::String t("Soon.");
    text.setString(t);
    text.setFont(font);
    text.setScale(2, 1);
    text.setStyle(sf::Text::Italic);
    text.setFillColor(sf::Color::Blue);
}

void SoonState::input(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        game->go_to_menu();
    }
}

void SoonState::update(const sf::Time delta) {

}

void SoonState::draw(sf::RenderWindow &window) {
    sf::Vector2i mid = sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2);
    shape.setPosition(sf::Vector2f(mid.x - 250, mid.y - 50));
    window.draw(shape);

    text.setPosition((float) mid.x - (float) text.getString().getSize() / 2.0f * 20.0f, (float) mid.y + 5);
    window.draw(text);
}
