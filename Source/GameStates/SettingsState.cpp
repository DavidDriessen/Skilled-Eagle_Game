//
// Created by robbie on 17-1-2017.
//

#include <SFML/Graphics/RenderWindow.hpp>
#include "SettingsState.h"
#include "../Game.h"

SettingsState::SettingsState(Game *pGame) : Menu(600, 500) {
    game = pGame;
    actions.push_back([&]() {
        res += direction;
        if (res < 0) { res = (int) (resA.size() - 1); }
        if (res >= resA.size()) { res = 0; }
    });
    actions.push_back([&]() {
        volume += (direction * 10);
        if (volume > 100) { volume = 0; }
        if (volume < 0) { volume = 100; }
    });
    actions.push_back([&]() { game->go_to_controls(); });
    actions.push_back([&]() { back(); });
}

void SettingsState::input(sf::Event &event) {
    direction = 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { direction = -1; }
    if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { back(); }
    btn[0] = sf::String("Resolution: ") + resA[res];
    btn[1] = sf::String("volume: ") + std::to_string(volume);
    Menu::input(event, game->get_Mouse_Position(), actions, true);
}


void SettingsState::update(const sf::Time delta) {
}

void SettingsState::draw(sf::RenderWindow &window) {
    Menu::draw(window, btn);
}

void SettingsState::setBack(const std::function<void()> &func) {
    back = func;
}
