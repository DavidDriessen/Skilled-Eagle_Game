//
// Created by robbie on 17-1-2017.
//

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "PlayState.h"
#include "../Game.h"

PlayState::PlayState(Game *pGame, SoundManager* soundManager, std::string map): level(map.c_str(), pGame) {
    game = pGame;
    this->soundManager = soundManager;
    soundManager->load_song((char *) "./assets/sounds/cyka.mp3");
    soundManager->play();
    beatDec = new BeatDetector(soundManager);
    bpm = beatDec->get_tempo();

    beatDec->add_listener(this);
    (*game->getControls()).assign_pressed(Left, [&]() { level.get_player().left(); });
    (*game->getControls()).assign_released(Left, [&]() { level.get_player().stop(); });
    (*game->getControls()).assign_pressed(Right, [&]() { level.get_player().right(); });
    (*game->getControls()).assign_released(Right, [&]() { level.get_player().stop(); });
    (*game->getControls()).assign_pressed(Jump, [&]() { level.get_player().up(); });
    (*game->getControls()).assign_pressed(Attack, [&]() { level.get_player().attack(); });
    (*game->getControls()).assign_pressed(GrabWeapon, [&]() { level.get_player().grab_for_weapon(level.get_weapons()); });
    (*game->getControls()).assign_pressed(ActivatePowerup, [&](){if(level.get_player().get_powerUp()){level.get_player().get_powerUp()->setActive(true);} });
    game->getOverlay()->addDebugValue("BPM", std::to_string(beatDec->get_tempo()));
}

void PlayState::input(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        game->go_to_pause();
    }
    else if (event.key.code == sf::Keyboard::H) {
        soundManager->change_pitch(0.01f);
    }

    else if (event.key.code == sf::Keyboard::J) {
        soundManager->change_pitch(-0.01f);
    }
    game->getControls()->run_actions(event);
    for (auto &object : level.get_blocks()) {
        object->input(event);
    }
    for (auto &object : level.get_finish()) {
        object->input(event);
    }
}

void PlayState::update(const sf::Time delta) {
    beatDec->update();
    pitch = soundManager->get_pitch();
    level.get_player().update(delta);
    for (auto &gun : level.get_weapons()) {
        if (level.get_player().get_weapon() != gun) {
            if(gun->check_collision(level.get_player())){
                game->go_to_level_select();
            }
        }
    }
    for (auto &object : level.get_powerUps()) {
        object->update(delta, level.get_player());
    }

    level.get_player().update(delta);
    level.get_player().setSpeed(bpm * pitch/400);
    if(level.get_player().get_powerUp()) {
        if (level.get_player().get_powerUp()->getActive() && !level.get_player().get_powerUp()->getUsed()) {
            switch (level.get_player().get_powerUp()->getFunction()) {
                case 0:
                    soundManager->change_pitch(-2 * soundManager->get_pitch());
                    break;
                case 1:
                    soundManager->change_pitch(0.5f);
                    break;
                case 2:
                    soundManager->change_pitch(-0.5f);
                    break;
                case 3:
                    soundManager->change_pitch(1);
                    break;
            }
            level.get_player().get_powerUp()->setUsed(true);
        }
        if (level.get_player().get_powerUp()->getActiveTime() > sf::seconds(5) && !level.get_player().get_powerUp()->getDone() && level.get_player().get_powerUp()->getActive()){
            switch (level.get_player().get_powerUp()->getFunction()) {
                case 0:
                    soundManager->change_pitch(-2 * soundManager->get_pitch());
                    break;
                case 1:
                    soundManager->change_pitch(-0.5f);
                    break;
                case 2:
                    soundManager->change_pitch(0.5f);
                    break;
                case 3:
                    soundManager->change_pitch(-1);
                    break;
            }
            level.get_player().get_powerUp()->setDone(true);
            level.get_player().get_powerUp()->setActive(false);
        }
    }

    for(auto &object : level.get_blocks()) {
    pitch = soundManager->get_pitch();
        object->update(delta);
    }
    for (auto &object : level.get_finish()) {
        if( level.get_player().get_rect().intersects(object->getFloatRect())) {
            game->go_to_level_select();
        }
        object->update(delta);
    }
    if (level.get_player().get_weapon() == nullptr) {
        level.get_player().grab_for_weapon(level.get_weapons());
    }
    int index = 0;
    for (auto &object : level.get_cyber_enforcers()) {
        object->update(delta);
        object->get_character()->grab_for_weapon(level.get_weapons());
        for (auto &gun : level.get_weapons()) {
            if ((*object->get_character()).get_weapon() != gun) {
                if (gun->check_collision(*object->get_character())) {
                    std::cout << "hbj\n";
                    level.get_cyber_enforcers().erase(level.get_cyber_enforcers().begin() + index);
                    break;
                }
            }
        }
        index++;
    }
    for (auto &gun : level.get_weapons()) {
        gun->update();
    }
    game->getOverlay()->addDebugValue("SPEED", std::to_string(level.get_player().getSpeed()));
}

void PlayState::draw(sf::RenderWindow &window) {
    game->getView()->setCenter(sf::Vector2f(level.get_player().getPosition().x, level.get_player().getPosition().y-(game->get_window()->getSize().y/6)));
    level.get_player().draw(window);
    for (auto &object : level.get_powerUps()) {
        object->draw(window);
    }
    for (auto &object : level.get_blocks()) {
        object->draw(window);
    }
    for (auto &object : level.get_finish()) {
        object->draw(window);
    }
    for (auto &object : level.get_cyber_enforcers()) {
        object->draw(window);
    }
    for (auto &object : level.get_weapons()) {
        object->draw(window);
    }
}

void PlayState::onBeat() {

}

void PlayState::onPeak(float peak) {

}

void PlayState::set_level(std::string map) {
    new (&level) Level(map.c_str(), game);
}
