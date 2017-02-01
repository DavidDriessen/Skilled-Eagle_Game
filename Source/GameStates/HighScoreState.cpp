//
// Created by david on 2/1/2017.
//

#include <dirent.h>
#include <sstream>
#include "HighScoreState.hpp"
#include "../Game.h"

HighScoreState::HighScoreState(Game *pGame) : Menu(pGame->getFonts().get(Fonts::Default), 600, 99999, 0, true) {
    game = pGame;
    load_levels();
}

void HighScoreState::input(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { game->go_to_menu(); }
    Menu::input(event, game->get_Mouse_Position(), actions);
}

void HighScoreState::update(const sf::Time delta) {

}

void HighScoreState::draw(sf::RenderWindow &window) {
    Menu::draw(window, btn);
}

void HighScoreState::load_score(std::string level) {
    while (!btn.empty()) { btn.pop_back(); }
    while (!actions.empty()) { actions.pop_back(); }
    std::cout << level;

    std::string line;
    std::ifstream f("./assets/Highscores/" + level);

    while (std::getline(f, line)) {
        std::stringstream linestream(line);
        std::string data;
        std::getline(linestream, data, '\n');
        btn.push_back(data.c_str());
        actions.push_back([]() {});
    }
}

void HighScoreState::load_levels() {
    while (!btn.empty()) { btn.pop_back(); }
    while (!actions.empty()) { actions.pop_back(); }

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("./assets/Highscores")) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != NULL) {
            if (sf::String(ent->d_name) != "." && sf::String(ent->d_name) != "..") {
                std::string name(sf::String(ent->d_name));
                btn.push_back(name.substr(0, name.length() - 4));
                actions.push_back([&, name]() {
                    load_score(name);
                });
            }
        }
        closedir(dir);
    } else {
        throw std::exception();
    }
}
