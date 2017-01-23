//
// Created by david on 1/23/2017.
//

#include "../Game.h"

PauseState::PauseState(Game *pGame) : Menu(600, 500, 1) {
    game = pGame;
    actions.push_back([&]() {});
    actions.push_back([&]() { game->go_to_play(); });
    actions.push_back([&]() { game->go_to_options(); });
    actions.push_back([&]() { game->go_to_menu(); });
}

void PauseState::input(sf::Event &event) {
    Menu::input(event, game->get_Mouse_Position(), actions);
}

void PauseState::update(const sf::Time delta) {
}

void PauseState::draw(sf::RenderWindow &window) {
    Menu::draw(window, btn);
}