//
// Created by endargon on 1/23/17.
//

#include <stdlib.h>
#include "SoundTestState.hpp"
#include "../Game.h"
#include <sstream>


SoundTestState::SoundTestState(Game *pGame, SoundManager *soundManager) : game(pGame) {
    this->soundManager = soundManager;
    font.loadFromFile("./assets/font.ttf");
    soundManager->load_song((char *) "./assets/sounds/cyka.mp3");
    soundManager->play();
    soundManager->pause();
    beatDec = new BeatDetector(soundManager);
    beat = beatDec->get_beat();
    cyka = sf::Text("CHEEKI BREEKI", font, 175);
    cyka.setPosition({30, 225});

    beatDec->add_listener(this);

}

SoundTestState::~SoundTestState() {

}

void SoundTestState::input(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        soundManager->pause();
    }
    else if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        soundManager->reset();
        game->go_to_menu();
    }
    else if (event.key.code == sf::Keyboard::H) {
        soundManager->change_pitch(0.01f);
    }

    else if (event.key.code == sf::Keyboard::J) {
        soundManager->change_pitch(-0.01f);
    }
}

void SoundTestState::update(const sf::Time delta) {
    cyka.setFillColor(sf::Color::Black);
    beatDec->update();
}

void SoundTestState::draw(sf::RenderWindow &window) {
    window.draw(cyka);
}


void SoundTestState::onBeat() {
    cyka.setFillColor(sf::Color::Yellow);
}