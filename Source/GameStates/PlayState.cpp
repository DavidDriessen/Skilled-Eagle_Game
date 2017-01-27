//
// Created by robbie on 17-1-2017.
//

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "PlayState.h"
#include "../Game.h"

PlayState::PlayState(Game *pGame, SoundManager* soundManager): level("assets/Levels/awesomeLevel.txt", pGame) {
    game = pGame;
    this->soundManager = soundManager;
    soundManager->load_song((char *) "./assets/sounds/cyka.mp3");
    soundManager->play();
    beatDec = new BeatDetector(soundManager);

    beatDec->add_listener(this);
    (*game->getControls()).assign_pressed(Left, [&]() { level.get_player().left(); });
    (*game->getControls()).assign_released(Left, [&]() { level.get_player().stop(); });
    (*game->getControls()).assign_pressed(Right, [&]() { level.get_player().right(); });
    (*game->getControls()).assign_released(Right, [&]() { level.get_player().stop(); });
    (*game->getControls()).assign_pressed(Jump, [&]() { level.get_player().up(); });
    (*game->getControls()).assign_pressed(Attack, [&]() { level.get_player().attack(); });
    (*game->getControls()).assign_pressed(GrabWeapon, [&]() { level.get_player().grab_for_weapon(level.get_weapons()); });
    (*game->getControls()).assign_pressed(ActivatePowerup, [&](){level.get_player().get_powerUp()->setActive(true); });
}

void PlayState::input(sf::Event &event) {
    if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        game->go_to_pause();
    }
    else if (event.key.code == sf::Keyboard::H) {
        soundManager->change_pitch(0.01f);
    }

    else if (event.key.code == sf::Keyboard::J) {
        soundManager->change_pitch(-0.01f);
    }
    game->getControls()->run_actions(event);
    for(auto &object : level.get_blocks()) {
        object->input(event);
    }
}

void PlayState::update(const sf::Time delta) {
    beatDec->update();
    level.get_player().update(delta);
    for(auto &object : level.get_powerUps()) {
        object->update(delta, level.get_player());
    }
    for(auto &object : level.get_blocks()) {
        object->update(delta);
    }
    if(level.get_player().get_weapon() == nullptr) {
        level.get_player().grab_for_weapon(level.get_weapons());
    }
    for(auto &object : level.get_cyber_enforcers()) {
        object->update(delta);
        object->get_character()->grab_for_weapon(level.get_weapons());
    }
    for(auto &gun : level.get_weapons()) {
        gun->update();
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
    for(auto &object : level.get_weapons()) {
        object->draw(window);
    }
}

void PlayState::onBeat() {

}

void PlayState::onPeak(float peak) {

}




