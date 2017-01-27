//
// Created by david on 1/27/2017.
//

#include <dirent.h>
#include "LevelSelectState.hpp"
#include "../Game.h"

LevelSelectState::LevelSelectState(Game *pGame) : Menu(pGame->getFonts().get(Fonts::Default), 600, 500) {
    game = pGame;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("./assets/Levels")) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != NULL) {
            if (sf::String(ent->d_name) != "." && sf::String(ent->d_name) != "..") {
                std::string name(sf::String(ent->d_name));
                btn.push_back(name.substr(0, name.length() - 4));
                actions.push_back([&, name]() {
                    game->set_level(name);
                    game->go_to_play();
                });
            }
        }
        closedir(dir);
    } else {
        throw std::exception();
    }
}

void LevelSelectState::input(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { game->go_to_menu(); }
    Menu::input(event, game->get_Mouse_Position(), actions);
}

void LevelSelectState::update(const sf::Time delta) {
}

void LevelSelectState::draw(sf::RenderWindow &window) {
    Menu::draw(window, btn);
}