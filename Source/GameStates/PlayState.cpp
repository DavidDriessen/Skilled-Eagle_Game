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
    std::string mapName = "assets/Levels/awesomeLevel.txt";
    level_objects = level.get_screen_objects_from_map(mapName);
}

void PlayState::input(sf::Event &event) {
    if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        game->go_to_menu();
    }
    for(auto &object : level_objects) {
        object->input(event);
    }
}

void PlayState::update(float delta) {
    std::cout << "updating PlayState \n";
    for(auto &object : level_objects) {
        object->update(delta);
    }
}

void PlayState::draw(sf::RenderWindow &window) {
    std::cout << "drawing PlayState \n";
    for(auto &object : level_objects) {
        object->draw(window);
    }
}




