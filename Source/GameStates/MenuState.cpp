//
// Created by robbie on 17-1-2017.
//

#include "MenuState.h"

MenuState::MenuState() {

}

MenuState::MenuState(Game *pGame) {
    game = pGame;
}

void MenuState::input(sf::Event &event) {
    if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        game->go_to_play();
    }
}

void MenuState::update(float delta) {
    std::cout << "updating MenuState \n";
}

void MenuState::draw(sf::RenderWindow &window) {
    std::vector<sf::String> l = {"lo", "nhi"};
    std::cout << "drawing MenuState \n";
    sf::RectangleShape shape({400, 400});
    window.draw(shape);
}