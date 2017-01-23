//
// Created by robbie on 17-1-2017.
//

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "PlayState.h"
#include "../Game.h"

PlayState::PlayState(Game *pGame): level("assets/Levels/awesomeLevel.txt") {
    game = pGame;

    (*game->getControlles()).assign_pressed(Left, [&]() { player.left(); });
    (*game->getControlles()).assign_released(Left, [&]() { player.stop(); });
    (*game->getControlles()).assign_pressed(Right, [&]() { player.right(); });
    (*game->getControlles()).assign_released(Right, [&]() { player.stop(); });
    (*game->getControlles()).assign_pressed(Jump, [&]() { player.up(); });
}

void PlayState::input(sf::Event &event) {
    if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        game->go_to_pause();
    }
    game->getControlles()->run_actions(event);
    for(auto &object : level.get_blocks()) {
        object->input(event);
    }
}

void PlayState::update(const sf::Time delta) {
    player.update(delta);
    for(auto &object : level.get_blocks()) {
        object->update(delta);
    }
}

void PlayState::draw(sf::RenderWindow &window) {
    player.draw(window);
    for(auto &object : level.get_blocks()) {
        object->draw(window);
    }
}




