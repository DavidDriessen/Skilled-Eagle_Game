//
// Created by david on 1/19/2017.
//

#include "ControllesState.hpp"
#include "../Game.h"

ControllesState::ControllesState(Game *pGame) : Menu(600, 500) {
    game = pGame;
    actions.push_back([&]() {

    });
    actions.push_back([&]() { game->go_to_options(); });
}

void ControllesState::input(sf::Event &event) {
    Menu::input(event, game->get_Mouse_Position(), actions, true);
}

void ControllesState::update(const sf::Time delta) {
}

void ControllesState::draw(sf::RenderWindow &window) {
    Menu::draw(window, btn);
}
