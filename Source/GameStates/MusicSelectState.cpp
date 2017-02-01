//
// Created by david on 1/27/2017.
//

#include <dirent.h>
#include "MusicSelectState.hpp"
#include "../Game.h"

MusicSelectState::MusicSelectState(Game *pGame) : Menu(pGame->getFonts().get(Fonts::Default), 600, 500) {
    game = pGame;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("./assets/sounds")) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != NULL) {
            if (sf::String(ent->d_name) != "." && sf::String(ent->d_name) != "..") {
                std::string name(sf::String(ent->d_name));
                if (name != "beats") {
                    btn.push_back(name.substr(0, name.length()));
                    actions.push_back([&, name]() {
                        std::string map = std::string("./assets/sounds/") + name;
                        game->getSoundManager()->insert_sound(SOUND_TYPES::GAME_SOUND, map);
                        game->go_to_play();
                    });
                }
            }
        }
        closedir(dir);
    } else {
        throw std::exception();
    }
}

void MusicSelectState::input(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { game->go_to_menu(); }
    Menu::input(event, game->get_Mouse_Position(), actions);
}

void MusicSelectState::update(const sf::Time delta) {
}

void MusicSelectState::draw(sf::RenderWindow &window) {
    Menu::draw(window, btn);
}