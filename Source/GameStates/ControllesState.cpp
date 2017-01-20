//
// Created by david on 1/19/2017.
//

#include "ControllesState.hpp"
#include "../Game.h"

ControllesState::ControllesState(Game *pGame) : Menu(600, 500) {
    game = pGame;
    key[Jump].key = sf::Keyboard::Key::Space;
    key[Left].key = sf::Keyboard::Key::Left;
    key[Right].key = sf::Keyboard::Key::Right;

    actions.push_back([&]() {
        key_to_bind = &key[Jump];
    });
    actions.push_back([&]() {
        key_to_bind = &key[Left];
    });
    actions.push_back([&]() {
        key_to_bind = &key[Right];
    });
}

void ControllesState::input(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed && key_to_bind) {
        if (event.key.code != sf::Keyboard::Key::Escape) {
            key_to_bind->key = event.key.code;
        }
        key_to_bind = NULL;
    } else {
        Menu::input(event, game->get_Mouse_Position(), actions, true);
    }
}

void ControllesState::update(const sf::Time delta) {
}

void ControllesState::draw(sf::RenderWindow &window) {
    if (key_to_bind) {

    } else {
        Menu::draw(window, btn);
    }
}

void ControllesState::asign_action(Actions &action, std::function<void()> &func) {
    key[action].action = func;
}

void ControllesState::run_actions(sf::Event &event) {
    for (auto &k:key) {
        if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(k.second.key)) {
            k.second.action();
        }
    }
}
