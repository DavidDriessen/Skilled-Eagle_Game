//
// Created by david on 1/19/2017.
//

#include <sstream>
#include "ControlsState.hpp"
#include "../Game.h"

ControlsState::ControlsState(Game *pGame) : Menu(pGame->getFonts().get(Fonts::Default), 600, 500) {
    game = pGame;
    font.loadFromFile("./assets/font.ttf");
    shape.setSize({500, 150});
    shape.setFillColor(sf::Color::Black);
    shape.setOutlineColor(sf::Color::Yellow);
    shape.setOutlineThickness(5);

    sf::String t("Press the key to bind.");
    text.setString(t);
    text.setFont(font);
    text.setScale(2, 1);
    text.setStyle(sf::Text::Italic);
    text.setFillColor(sf::Color::Blue);

    std::string line;
    std::ifstream f("./assets/Settings/Controls.txt");

    for (int i = 0; i < ActionsCount; ++i) {
        if (std::getline(f, line)) {
            std::stringstream linestream(line);
            std::string data;
            std::getline(linestream, data, '\n');
            key[(Actions) i].key = (sf::Keyboard::Key) atoi(data.c_str());
        }
    }

    actions.push_back([&]() {
        key_to_bind = &key[Jump];
    });
    actions.push_back([&]() {
        key_to_bind = &key[Left];
    });
    actions.push_back([&]() {
        key_to_bind = &key[Right];
    });
    actions.push_back([&]() {
        key_to_bind = &key[Attack];
    });
    actions.push_back([&]() {
        key_to_bind = &key[GrabWeapon];
    });
    actions.push_back([&](){
        key_to_bind = &key[ActivatePowerup];
    });
    key_to_bind = NULL;
}

void ControlsState::input(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed && key_to_bind) {
        if (event.key.code != sf::Keyboard::Key::Escape) {
            key_to_bind->key = event.key.code;
        }
        key_to_bind = NULL;
    } else {
        if (event.type == sf::Event::KeyPressed &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            game->go_to_options();
            save();
        }
        Menu::input(event, game->get_Mouse_Position(), actions, true);
    }
}

void ControlsState::update(const sf::Time delta) {
}

void ControlsState::draw(sf::RenderWindow &window) {
    if (key_to_bind) {
        sf::Vector2i mid = sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2);
        shape.setPosition(sf::Vector2f(mid.x - 250, mid.y - 50));
        window.draw(shape);

        text.setPosition((float) mid.x - (float) text.getString().getSize() / 2.0f * 20.0f, (float) mid.y + 5);
        window.draw(text);
    } else {
        btn[0] = sf::String("Jump: ") + KeyboardKeyNames[key[Jump].key];
        btn[1] = sf::String("Left: ") + KeyboardKeyNames[key[Left].key];
        btn[2] = sf::String("Right: ") + KeyboardKeyNames[key[Right].key];
        btn[3] = sf::String("Attack: ") + KeyboardKeyNames[key[Attack].key];
        btn[4] = sf::String("Grab Weapon: ") + KeyboardKeyNames[key[GrabWeapon].key];
        btn[5] = sf::String("Activate Powerup: ") + KeyboardKeyNames[key[ActivatePowerup].key];
        Menu::draw(window, btn);
    }
}

void ControlsState::assign_pressed(const Actions &action, const std::function<void()> &func) {
    key[action].pressed = func;
}

void ControlsState::assign_released(const Actions &action, const std::function<void()> &func) {
    key[action].released = func;
}

void ControlsState::run_actions(sf::Event &event) {
    for (auto &k:key) {
        if (event.key.code == k.second.key) {
            if (event.type == sf::Event::KeyPressed) {
                k.second.pressed();
            } else if (event.type == sf::Event::KeyReleased) {
                k.second.released();
            }
        }
    }
}

void ControlsState::save() {
    std::ofstream f("./assets/Settings/Controls.txt");
    f.clear();
    std::string *data = new std::string[ActionsCount];
    for (auto &k: key) {
        //data[k.first].append(std::to_string(k.second.key));
        data[k.first].append("\n");
    }
    for (int i = 0; i < ActionsCount; i++) {
        f.write(data[i].c_str(), data[i].size());
    }
    f.close();
}
