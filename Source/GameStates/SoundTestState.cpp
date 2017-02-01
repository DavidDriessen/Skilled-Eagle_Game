//
// Created by endargon on 1/23/17.
//

#include <stdlib.h>
#include "SoundTestState.hpp"
#include "../Game.h"
#include <sstream>


SoundTestState::SoundTestState(Game *pGame, SoundManager *soundManager) : game(pGame) {
    game = pGame;
    this->soundManager =  game->getSoundManager();;
    font.loadFromFile("./assets/font.ttf");
    beatDec = new BeatDetector(soundManager, SOUND_TYPES::GAME_SOUND);
    beat = beatDec->get_beat();
    soundManager->play(SOUND_TYPES::GAME_SOUND);
    cyka = sf::Text("CHEEKI BREEKI", font, 175);
    cyka.setPosition({30, 225});

    beatDec->add_listener(this);

}

SoundTestState::~SoundTestState() {

}

void SoundTestState::input(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        soundManager->pause(SOUND_TYPES::GAME_SOUND);
    }
    else if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        soundManager->reset(SOUND_TYPES::GAME_SOUND);
        game->go_to_menu(true);
    }
    else if (event.key.code == sf::Keyboard::H) {
        soundManager->change_pitch(0.01f, SOUND_TYPES::GAME_SOUND);
    }

    else if (event.key.code == sf::Keyboard::J) {
        soundManager->change_pitch(-0.01f, SOUND_TYPES::GAME_SOUND);
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