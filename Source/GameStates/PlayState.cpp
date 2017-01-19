//
// Created by robbie on 17-1-2017.
//

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "PlayState.h"
#include "../Game.h"

PlayState::PlayState() {

}

PlayState::PlayState(Game *pGame) {
    game = pGame;
}

void PlayState::input(sf::Event &event) {
    if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        game->go_to_menu();
    }
}

void PlayState::update(float delta) {
    std::cout << "updating PlayState \n";
}

void PlayState::draw(sf::RenderWindow &window) {
    std::cout << "drawing PlayState \n";
    sf::RectangleShape shape({200, 200});
    window.draw(shape);
}




