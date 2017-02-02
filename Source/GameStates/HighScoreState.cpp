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

void HighScoreState::load_score(std::string level, bool sort) {
    while (!btn.empty()) { btn.pop_back(); }
    while (!actions.empty()) { actions.pop_back(); }

    std::string line;
    std::ifstream f("./assets/Highscores/" + level);

    while (std::getline(f, line)) {
        std::stringstream linestream(line);
        std::string data;
        std::getline(linestream, data, '\n');
        btn.push_back(data.c_str());
        actions.push_back([]() {});
    }

    if (sort) {
        std::sort(btn.begin(), btn.end(),
                  [](std::string i, std::string j) { return atoi(i.c_str()) > atoi(j.c_str()); });
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

void HighScoreState::add_score(std::string level, int score) {
    std::ofstream output;
    output.open("./assets/Highscores/" + level, std::ios_base::app);
    output << score << "\n";
    output.close();
}

void HighScoreState::set_current_score(int score) {
    this->score = score;
}

int HighScoreState::get_current_score() {
    return score;
}

int HighScoreState::get_latest_score(std::string level) {
    load_score(level, false);
    return atoi(std::string(btn[btn.size() - 1]).c_str());
}

int HighScoreState::get_highest_score(std::string level) {
    load_score(level);
    return atoi(std::string(btn[0]).c_str());
}
