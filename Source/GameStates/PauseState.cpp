//
// Created by david on 1/23/2017.
//

#include "../Game.h"

PauseState::PauseState(Game *pGame) : Menu(pGame->getFonts().get(Fonts::Default), 600, 500, 1) {
    game = pGame;
    actions.push_back([&]() {});
    actions.push_back([&]() { game->go_to_play(); });
    actions.push_back([&]() { game->go_to_options(); });
    actions.push_back([&]() { game->go_to_menu(); });
}

void PauseState::input(sf::Event &event) {
    if(event.type == sf::Event::KeyPressed &&
       sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        game->go_to_play();
    }
    Menu::input(event, game->get_Mouse_Position(), actions);
}

void PauseState::update(const sf::Time delta) {
}

void PauseState::draw(sf::RenderWindow &window) {
    //btn[0] = sf::String("HighScore: ") + std::to_string(temp);
    Menu::draw(window, btn);
}