//
// Created by robbie on 17-1-2017.
//

#include "MenuState.h"
#include "../Game.h"

MenuState::MenuState(Game *pGame) : Menu(600, 500) {
    game = pGame;
    actions.push_back([&]() { game->go_to_play(); });
    actions.push_back([&]() { game->go_to_test(); });
    actions.push_back([&]() { game->go_to_soon(); });
    actions.push_back([&]() { game->go_to_soon(); });
    actions.push_back([&]() { game->go_to_options(); });
    actions.push_back([&]() { game->quit(); });
}

void MenuState::input(sf::Event &event) {
    Menu::input(event, game->get_Mouse_Position(), actions);
}

void MenuState::update(const sf::Time delta) {
}

void MenuState::draw(sf::RenderWindow &window) {
    Menu::draw(window, btn);
}