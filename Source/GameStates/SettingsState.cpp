//
// Created by robbie on 17-1-2017.
//

#include <SFML/Graphics/RenderWindow.hpp>
#include <sstream>
#include "SettingsState.h"
#include "../Game.h"

SettingsState::SettingsState(Game *pGame) : Menu(pGame->getFonts().get(Fonts::Default), 600, 500) {
    game = pGame;
    actions.push_back([&]() {
        res += direction;
        if (res < 0) { res = (int) (resA.size() - 1); }
        if (res >= resA.size()) { res = 0; }
    });
    actions.push_back([&]() {
        volume += direction;
        if (volume > 100) { volume = 0; }
        if (volume < 0) { volume = 100; }
        game->getSoundManager()->set_volume(volume / 100);
    });
    actions.push_back([&]() { game->go_to_controls(); });
    actions.push_back([&]() { save(); back(); });

    std::string line;
    std::ifstream f("./assets/Settings/Settings.txt");

    //resolution
    if (std::getline(f, line)) {
        std::stringstream linestream(line);
        std::string data;
        std::getline(linestream, data, '\n');
        oldres = res = atoi(data.c_str());
    }
    //volume
    if (std::getline(f, line)) {
        std::stringstream linestream(line);
        std::string data;
        std::getline(linestream, data, '\n');
        oldVolume = volume = atoi(data.c_str());
    }
    f.close();
//    game->get_window()->setSize(resV[res]);
    game->get_window()->create(sf::VideoMode(resV[res].x, resV[res].y), "waveForms",
                               (res == 0) ? sf::Style::Fullscreen : sf::Style::Default);
    game->getSoundManager()->set_volume(volume / 100);
}

void SettingsState::input(sf::Event &event) {
    direction = 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { direction = -1; }
    if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        volume = oldVolume;
        res = oldres;
        game->getSoundManager()->set_volume(volume / 100);
        back();
    }
    btn[0] = sf::String("Resolution: ") + resA[res];
    btn[1] = sf::String("volume: ") + std::to_string((int) volume);
    Menu::input(event, game->get_Mouse_Position(), actions, true);
}


void SettingsState::update(const sf::Time delta) {
}

void SettingsState::draw(sf::RenderWindow &window) {
    Menu::draw(window, btn);
}

void SettingsState::setBack(const std::function<void()> &func) {
    back = func;
}

void SettingsState::save() {
    std::ofstream f("./assets/Settings/Settings.txt");
    f.clear();

//    game->get_window()->setSize(resV[res]);
    game->get_window()->create(sf::VideoMode(resV[res].x, resV[res].y), "waveForms",
                               (res == 0) ? sf::Style::Fullscreen : sf::Style::Default);
    oldres = res;
    std::string resolution = std::to_string(res) + "\n";
    f.write(resolution.c_str(), resolution.size());

    oldVolume = volume;
    std::string vol = std::to_string(volume) + "\n";
    f.write(vol.c_str(), vol.size());

    f.close();
}
