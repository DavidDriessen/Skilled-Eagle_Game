//
// Created by david on 2/1/2017.
//

#include "HighScoreState.hpp"
#include "../Game.h"

HighScoreState::HighScoreState(Game *pGame) : Menu(pGame->getFonts().get(Fonts::Default), 600, 99999, 0, true) {
    game = pGame;
}

void HighScoreState::input(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { game->go_to_menu(); }
    Menu::input(event, game->get_Mouse_Position(), actions);
}

void HighScoreState::update(const sf::Time delta) {

}

void HighScoreState::draw(sf::RenderWindow &window) {
    Menu::draw(window, btn);
}

void HighScoreState::load_score() {
    while (!btn.empty()) { btn.pop_back(); }
    while (!actions.empty()) { actions.pop_back(); }

    for (int i = 0; i < 5; ++i) {
        btn.push_back(sf::String("Pos: ") + std::to_string(i));
        actions.push_back([](){});
    }
}
