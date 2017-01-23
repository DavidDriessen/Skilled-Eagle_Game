//
// Created by robbie on 17-1-2017.
//

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "PlayState.h"
#include "../Game.h"

PlayState::PlayState(Game *pGame): level("assets/Levels/awesomeLevel.txt") {
    game = pGame;

    (*game->getControls()).assign_pressed(Left, [&]() { player.left(); });
    (*game->getControls()).assign_released(Left, [&]() { player.stop(); });
    (*game->getControls()).assign_pressed(Right, [&]() { player.right(); });
    (*game->getControls()).assign_released(Right, [&]() { player.stop(); });
    (*game->getControls()).assign_pressed(Jump, [&]() { player.up(); });
}

void PlayState::input(sf::Event &event) {
    if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        game->go_to_pause();
    }
    game->getControls()->run_actions(event);
    for(auto &object : level.get_blocks()) {
        object->input(event);
    }
}

void PlayState::update(const sf::Time delta) {
    level.get_player().update(delta);
    for(auto &object : level.get_powerUps()) {
        object->update(delta, level.get_player());
    }
    for(auto &object : level.get_blocks()) {
        object->update(delta);
    }
    for(auto &object : level.get_cyber_enforcers()) {
        object->update(delta);
    }
}

void PlayState::draw(sf::RenderWindow &window) {
    level.get_player().draw(window);
    for(auto &object : level.get_powerUps()) {
        object->draw(window);
    }
    for(auto &object : level.get_blocks()) {
        object->draw(window);
    }
    for(auto &object : level.get_cyber_enforcers()) {
        object->draw(window);
    }
}