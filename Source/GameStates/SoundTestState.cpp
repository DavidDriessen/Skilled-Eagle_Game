//
// Created by endargon on 1/23/17.
//

#include "SoundTestState.hpp"
#include "../Game.h"

SoundTestState::SoundTestState(Game *pGame, FmodApi *fmod) : game(pGame), fmod(fmod) {
    fmod->add_song("song", "./assets/sounds/song.mp3");
}

SoundTestState::~SoundTestState() {

}

void SoundTestState::input(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        fmod->toggle_play("song");
    }
    if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
        fmod->stop_song("song");
        game->go_to_menu();
    }
}

void SoundTestState::update(const sf::Time delta) {
    fmod->update();
}

void SoundTestState::draw(sf::RenderWindow &window) {
    int maxVol = fmod->get_current_peak();
    sf::RectangleShape shape;
    shape.setSize({20, 20});
    shape.setFillColor(sf::Color::Red);
    shape.setScale({1, 1});
    shape.setPosition({window.getSize().x / 2, window.getSize().y / 2});
    if (maxVol > 0) {
        int height = ((float) window.getSize().y / (float) 100) * (float) maxVol / ((float) 4000 / (float) 100);
        shape.setSize({window.getSize().x, height});
        shape.setPosition({0, window.getSize().y - shape.getSize().y});
    }
    window.clear();
    window.draw(shape);
    window.display();
}









