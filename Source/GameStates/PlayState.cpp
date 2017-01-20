//
// Created by robbie on 17-1-2017.
//

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "PlayState.h"
#include "../Game.h"

PlayState::PlayState(Game *pGame): level("assets/Levels/awesomeLevel.txt") {
    game = pGame;
}

PlayState::~PlayState() {

}

void PlayState::input(sf::Event &event) {
    if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        game->go_to_menu();
    }
}

void PlayState::update(const sf::Time delta) {

}

void PlayState::draw(sf::RenderWindow &window) {
    for(auto &block : level.get_blocks()) {
        block->draw(window);
    }
}




