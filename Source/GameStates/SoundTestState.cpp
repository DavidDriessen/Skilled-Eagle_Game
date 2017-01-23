//
// Created by endargon on 1/23/17.
//

#include <stdlib.h>
#include "SoundTestState.hpp"
#include "../Game.h"

SoundTestState::SoundTestState(Game *pGame, FmodApi *fmod) : game(pGame), fmod(fmod) {
    fmod->add_song("song", "./assets/sounds/song.mp3");
    fmod->add_song("song1", "./assets/sounds/song1.mp3");
    fmod->add_song("song2", "./assets/sounds/song3.mp3");
//    shape.setSize({game->get_window()->getSize().x, 0});
//    shape.setFillColor(sf::Color::Red);
//    shape.setScale({1, 1});
//    shape.setPosition({game->get_window()->getSize().x / 2, game->get_window()->getSize().y / 2});
      for(int i = 0; i < 512; i++) {
          shapes[i] = new sf::RectangleShape;
          shapes[i]->setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));

      }
}

SoundTestState::~SoundTestState() {

}

void SoundTestState::input(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        fmod->toggle_play("song1");
    }
    if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
        fmod->stop_song("song1");
        game->go_to_menu();
    }
}

void SoundTestState::update(const sf::Time delta) {
    fmod->update();
}

void SoundTestState::draw(sf::RenderWindow &window) {
//    int maxVol = fmod->get_current_peak();
//    if (maxVol > 0) {
//        int height = ((float) window.getSize().y / (float) 100) * (float) maxVol / ((float) 4000 / (float) 100);
//        shape.setSize({window.getSize().x, height});
//        shape.setPosition({0, window.getSize().y - shape.getSize().y});
//    }
//    window.draw(shape);
    int blockGap = 4 / (512 / 64);
    int blockWidth = int((int(window.getSize().x) * 2.0f) / int(512) - blockGap);
    int blockMaxHeight = 200;
    float *spec = fmod->get_spec();
    std::cout << spec[0] << std::endl;
// Parameters: Left-hand X co-ordinate of bar, left-hand Y co-ordinate of bar, width of bar, height of bar (negative to draw upwards), paintbrush to use

    for (int b = 0; b < 512 - 1; b++) {
        sf::RectangleShape *t = shapes[b];
        t->setPosition({int(0.1f + (blockWidth + blockGap) * b), window.getSize().y});
        t->setSize({blockWidth, int(-blockMaxHeight * spec[b])});
        window.draw(*t);
    }
}









