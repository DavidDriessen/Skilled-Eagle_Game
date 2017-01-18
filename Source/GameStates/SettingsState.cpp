//
// Created by robbie on 17-1-2017.
//

#include <SFML/Graphics/RenderWindow.hpp>
#include "SettingsState.h"
#include "../Game.h"

SettingsState::SettingsState() {

}

void SettingsState::input(sf::Event &event) {

}


void SettingsState::update(const sf::Time delta) {
    std::cout << "update SettingsState \n";
}

void SettingsState::draw(sf::RenderWindow &window) {
    std::cout << "draw SettingsState \n";

}

SettingsState::SettingsState(Game *pGame) {
    game = pGame;
}

